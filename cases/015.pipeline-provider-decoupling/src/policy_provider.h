#pragma once

#include <string>

#include "policy.h"

namespace nitr::case015 {

class PolicyProvider {
 public:
  virtual ~PolicyProvider() = default;
  virtual Policy Lookup(const std::string& source_id) const = 0;
};

}  // namespace nitr::case015
