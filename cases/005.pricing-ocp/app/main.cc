// Copyright (c) Haichao Zhu
// SPDX-License-Identifier: Apache-2.0

#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "pricing.h"

using json = nlohmann::json;

static bool ReadJson(const std::string& path, json* j) {
  if (!j) {
    return false;
  }
  std::ifstream ifs(path);
  if (!ifs.is_open()) {
    return false;
  }
  try {
    ifs >> *j;
  } catch (...) {
    return false;
  }
  return true;
}

static bool WriteJson(const std::string& path, const json& j) {
  std::ofstream ofs(path);
  if (!ofs.is_open()) {
    return false;
  }
  ofs << j.dump(2) << "\n";
  return true;
}

static int ParseMilestone(const std::string& s) {
  if (s == "m1") {
    return 1;
  }
  if (s == "m2") {
    return 2;
  }
  if (s == "m3") {
    return 3;
  }
  if (s == "m4") {
    return 4;
  }
  return -1;
}

static bool IsFiniteNumber(const json& v) {
  if (!v.is_number()) {
    return false;
  }
  const double x = v.get<double>();
  return std::isfinite(x);
}

int main(int argc, char** argv) {
  std::string in_path;
  std::string out_path;
  std::string milestone_str;
  std::string rules_path;  // parsed but not used in minimal skeleton

  for (int i = 1; i < argc; ++i) {
    const std::string a = argv[i];
    if (a == "--in" && i + 1 < argc) {
      in_path = argv[++i];
    } else if (a == "--out" && i + 1 < argc) {
      out_path = argv[++i];
    } else if (a == "--milestone" && i + 1 < argc) {
      milestone_str = argv[++i];
    } else if (a == "--rules" && i + 1 < argc) {
      rules_path = argv[++i];
    }
  }

  if (in_path.empty() || out_path.empty() || milestone_str.empty()) {
    std::cerr << "ERR_IO\n";
    return 1;
  }

  const int milestone = ParseMilestone(milestone_str);
  if (milestone < 0) {
    std::cerr << "ERR_UNSUPPORTED_MILESTONE\n";
    return 1;
  }

  json j;
  if (!ReadJson(in_path, &j)) {
    std::cerr << "ERR_INVALID_JSON\n";
    return 1;
  }
  if (!j.is_object()) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return 1;
  }

  // ---- Schema validation ----
  // subtotal: number, finite, >= 0
  if (!j.contains("subtotal") || !IsFiniteNumber(j["subtotal"])) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return 1;
  }
  const double subtotal = j["subtotal"].get<double>();
  if (subtotal < 0.0) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return 1;
  }

  // is_member: boolean
  if (!j.contains("is_member") || !j["is_member"].is_boolean()) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return 1;
  }

  // items: integer, >= 0
  if (!j.contains("items") || !j["items"].is_number_integer()) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return 1;
  }
  const int items = j["items"].get<int>();
  if (items < 0) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return 1;
  }

  // coupons: array of strings
  std::vector<std::string> coupons;
  if (j.contains("coupons")) {
    if (!j["coupons"].is_array()) {
      std::cerr << "ERR_INVALID_SCHEMA\n";
      return 1;
    }
    for (const auto& c : j["coupons"]) {
      if (!c.is_string()) {
        std::cerr << "ERR_INVALID_SCHEMA\n";
        return 1;
      }
      coupons.push_back(c.get<std::string>());
    }
  }

  // Convert dollars -> cents (rounded to nearest cent).
  const int64_t subtotal_cents =
      static_cast<int64_t>(std::llround(subtotal * 100.0));

  nitr::case005::Order order;
  order.subtotal_cents = subtotal_cents;
  order.is_member = j["is_member"].get<bool>();
  order.items = items;
  order.coupons = std::move(coupons);

  // ---- Compute ----
  nitr::case005::PriceResult res =
      nitr::case005::ComputeFinalPrice(order, milestone);

  // ---- Output (USD number with 2 decimals) ----
  json out;
  out["final_price"] = static_cast<double>(res.final_price_cents) / 100.0;
  out["applied_rules"] = res.applied_rules;

  if (!WriteJson(out_path, out)) {
    std::cerr << "ERR_IO\n";
    return 1;
  }

  return 0;
}
