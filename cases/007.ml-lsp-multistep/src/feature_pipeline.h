#ifndef SOLID_FEATURE_PIPELINE_H_
#define SOLID_FEATURE_PIPELINE_H_

#include <memory>
#include <vector>

#include "feature_transform.h"

namespace nitr::case007 {

class FeaturePipeline {
 public:
  explicit FeaturePipeline(std::unique_ptr<FeatureTransform> transform);

  std::vector<float> Run(const std::vector<float>& features) const;

 private:
  std::unique_ptr<FeatureTransform> transform_;
};

}  // namespace nitr::case007

#endif  // SOLID_FEATURE_PIPELINE_H_
