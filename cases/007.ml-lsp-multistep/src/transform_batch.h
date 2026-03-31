#ifndef SOLID_TRANSFORM_BATCH_H_
#define SOLID_TRANSFORM_BATCH_H_

#include <vector>

#include "feature_transform.h"

namespace nitr::case007 {

std::vector<std::vector<float>> TransformBatch(
    const FeatureTransform& transform,
    const std::vector<std::vector<float>>& batch);

}  // namespace nitr::case007

#endif  // SOLID_TRANSFORM_BATCH_H_
