#include "feature_pipeline.h"

namespace nitr::case007 {

FeaturePipeline::FeaturePipeline(std::unique_ptr<FeatureTransform> transform)
    : transform_(std::move(transform)) {}

std::vector<float> FeaturePipeline::Run(
    const std::vector<float>& features) const {
  return transform_->Transform(features);
}

}  // namespace nitr::case007
