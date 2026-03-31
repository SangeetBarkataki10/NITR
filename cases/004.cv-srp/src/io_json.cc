#include "io_json.h"

#include <fstream>
#include <nlohmann/json.hpp>

namespace nitr::case004 {
namespace {

bool ReadAll(const std::string& path, std::string* out) {
  std::ifstream ifs(path);
  if (!ifs) {
    return false;
  }
  out->assign((std::istreambuf_iterator<char>(ifs)),
              std::istreambuf_iterator<char>());
  return true;
}

}  // namespace

ParseOutput ParsePairJsonFromFile(const std::string& path) {
  ParseOutput out;
  std::string text;
  if (!ReadAll(path, &text)) {
    out.err = ErrorCode::kInvalidJson;
    return out;
  }

  nlohmann::json j;
  try {
    j = nlohmann::json::parse(text);
  } catch (...) {
    out.err = ErrorCode::kInvalidJson;
    return out;
  }

  // TODO: full schema validation per spec.
  // Minimal placeholder validation:
  if (!j.contains("camera") || !j.contains("frame0") || !j.contains("frame1") ||
      !j.contains("matches") || !j.contains("options")) {
    out.err = ErrorCode::kInvalidSchema;
    return out;
  }

  PairInput in;
  try {
    auto& c = j.at("camera");
    in.cam.fx = c.at("fx").get<double>();
    in.cam.fy = c.at("fy").get<double>();
    in.cam.cx = c.at("cx").get<double>();
    in.cam.cy = c.at("cy").get<double>();

    auto& f0 = j.at("frame0").at("keypoints");
    auto& f1 = j.at("frame1").at("keypoints");
    for (auto& kp : f0) {
      in.f0.keypoints_px.push_back(
          {kp.at(0).get<double>(), kp.at(1).get<double>()});
    }
    for (auto& kp : f1) {
      in.f1.keypoints_px.push_back(
          {kp.at(0).get<double>(), kp.at(1).get<double>()});
    }

    for (auto& m : j.at("matches")) {
      in.matches.push_back({m.at(0).get<int>(), m.at(1).get<int>()});
    }

    auto& opt = j.at("options");
    in.opt.model = opt.at("model").get<std::string>();
    in.opt.ransac_thresh_px = opt.at("ransac_thresh_px").get<double>();
    in.opt.max_iters = opt.at("max_iters").get<int>();
    if (opt.contains("seed")) {
      in.opt.seed = opt.at("seed").get<uint32_t>();
    }
  } catch (...) {
    out.err = ErrorCode::kInvalidSchema;
    return out;
  }

  // Minimal constraint checks
  if (in.cam.fx <= 0.0 || in.cam.fy <= 0.0 || in.f0.keypoints_px.empty() ||
      in.f1.keypoints_px.empty() || in.opt.ransac_thresh_px <= 0.0 ||
      in.opt.max_iters < 1) {
    out.err = ErrorCode::kInvalidSchema;
    return out;
  }

  // Match index range check
  for (const auto& m : in.matches) {
    if (m.i0 < 0 || m.i0 >= static_cast<int>(in.f0.keypoints_px.size()) ||
        m.i1 < 0 || m.i1 >= static_cast<int>(in.f1.keypoints_px.size())) {
      out.err = ErrorCode::kInvalidSchema;
      return out;
    }
  }

  out.input = in;
  out.err = ErrorCode::kOk;
  return out;
}

ErrorCode WriteResultJsonToFile(const std::string& path, const PairInput& in,
                                const EstimationOutput& est, const Metrics& m,
                                Decision d) {
  nlohmann::json j;
  j["model"] = est.model.type;

  // params
  nlohmann::json mat = nlohmann::json::array();
  for (int r = 0; r < 3; ++r) {
    nlohmann::json row = nlohmann::json::array();
    for (int c = 0; c < 3; ++c) {
      row.push_back(est.model.mat3x3[r * 3 + c]);
    }
    mat.push_back(row);
  }
  j["params"] = {{"E", mat}};

  // inliers
  nlohmann::json inl = nlohmann::json::array();
  for (bool b : est.inliers) {
    inl.push_back(b);
  }
  j["inliers"] = inl;

  // metrics
  j["metrics"] = {
      {"num_matches", m.num_matches},
      {"num_inliers", m.num_inliers},
      {"inlier_ratio", m.inlier_ratio},
      {"median_sampson_error", m.median_sampson_error},
  };

  j["decision"] = (d == Decision::kAccept) ? "ACCEPT" : "REJECT";

  std::ofstream ofs(path);
  if (!ofs) {
    return ErrorCode::kInvalidJson;
  }
  ofs << j.dump(2);
  return ErrorCode::kOk;
}

}  // namespace nitr::case004
