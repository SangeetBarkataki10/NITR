#include "transform_chain.h"

namespace nitr::case007 {

void TransformChain::AddStep(std::unique_ptr<FeatureTransform> transform) {
  steps_.push_back(std::move(transform));
}

std::vector<float> TransformChain::Transform(
    const std::vector<float>& input) const {
  return input;
}

}  // namespace nitr::case007
