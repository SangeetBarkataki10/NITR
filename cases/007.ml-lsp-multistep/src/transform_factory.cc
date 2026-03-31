#include "transform_factory.h"

#include <stdexcept>

#include "clamp_transform.h"
#include "identity_transform.h"
#include "l2_normalize_transform.h"

namespace nitr::case007 {

std::unique_ptr<FeatureTransform> MakeTransform(const std::string& name) {
  if (name == "identity") {
    return std::make_unique<IdentityTransform>();
  }
  if (name == "l2") {
    return std::make_unique<L2NormalizeTransform>();
  }
  if (name == "clamp") {
    return std::make_unique<ClampTransform>();
  }
  throw std::invalid_argument("unknown transform: " + name);
}

}  // namespace nitr::case007
