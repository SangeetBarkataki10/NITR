#ifndef SOLID_L2_NORMALIZE_TRANSFORM_H_
#define SOLID_L2_NORMALIZE_TRANSFORM_H_

#include "feature_transform.h"

namespace nitr::case007 {

class L2NormalizeTransform : public FeatureTransform {
 public:
  std::vector<float> Transform(const std::vector<float>& input) const override;
};

}  // namespace nitr::case007

#endif  // SOLID_L2_NORMALIZE_TRANSFORM_H_
