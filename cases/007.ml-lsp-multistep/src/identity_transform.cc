#include "identity_transform.h"

namespace nitr::case007 {

std::vector<float> IdentityTransform::Transform(
    const std::vector<float>& input) const {
  return input;
}

}  // namespace nitr::case007
