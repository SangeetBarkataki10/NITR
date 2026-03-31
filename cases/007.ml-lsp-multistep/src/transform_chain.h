#ifndef SOLID_TRANSFORM_CHAIN_H_
#define SOLID_TRANSFORM_CHAIN_H_

#include <memory>
#include <vector>

#include "feature_transform.h"

namespace nitr::case007 {

class TransformChain : public FeatureTransform {
 public:
  void AddStep(std::unique_ptr<FeatureTransform> transform);

  std::vector<float> Transform(const std::vector<float>& input) const override;

 private:
  std::vector<std::unique_ptr<FeatureTransform>> steps_;
};

}  // namespace nitr::case007

#endif  // SOLID_TRANSFORM_CHAIN_H_
