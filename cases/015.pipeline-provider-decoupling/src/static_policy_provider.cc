#include "static_policy_provider.h"

namespace nitr::case015 {

StaticPolicyProvider::StaticPolicyProvider()
    : policies_{{"web", Policy{"silver", 45}},
                {"mobile", Policy{"gold", 90}},
                {"partner", Policy{"archive", 180}}} {}

Policy StaticPolicyProvider::Lookup(const std::string& source_id) const {
  const auto it = policies_.find(source_id);
  if (it == policies_.end()) {
    return Policy::Fallback();
  }
  return it->second;
}

}  // namespace nitr::case015
