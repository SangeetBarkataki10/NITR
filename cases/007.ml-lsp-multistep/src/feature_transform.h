#ifndef SOLID_FEATURE_TRANSFORM_H_
#define SOLID_FEATURE_TRANSFORM_H_

#include <vector>

namespace nitr::case007 {

class FeatureTransform {
 public:
  virtual ~FeatureTransform() = default;

  virtual std::vector<float> Transform(
      const std::vector<float>& input) const = 0;
};

}  // namespace nitr::case007

#endif  // SOLID_FEATURE_TRANSFORM_H_
