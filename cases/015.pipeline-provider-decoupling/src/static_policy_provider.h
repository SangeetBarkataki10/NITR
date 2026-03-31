#pragma once

#include <string>
#include <unordered_map>

#include "policy_provider.h"

namespace nitr::case015 {

class StaticPolicyProvider : public PolicyProvider {
 public:
  StaticPolicyProvider();
  Policy Lookup(const std::string& source_id) const override;

 private:
  std::unordered_map<std::string, Policy> policies_;
};

}  // namespace nitr::case015
