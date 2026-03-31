#ifndef SOLID_CLAMP_TRANSFORM_H_
#define SOLID_CLAMP_TRANSFORM_H_

#include "feature_transform.h"

namespace nitr::case007 {

class ClampTransform : public FeatureTransform {
 public:
  std::vector<float> Transform(const std::vector<float>& input) const override;
};

}  // namespace nitr::case007

#endif  // SOLID_CLAMP_TRANSFORM_H_
