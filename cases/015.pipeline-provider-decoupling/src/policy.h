#pragma once

#include <string>

namespace nitr::case015 {

struct Policy {
  std::string policy_tier;
  int retention_days = 30;

  static Policy Fallback() {
    return Policy{"standard", 30};
  }
};

}  // namespace nitr::case015
