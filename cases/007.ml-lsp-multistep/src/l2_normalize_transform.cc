#include "l2_normalize_transform.h"

#include <cmath>

namespace nitr::case007 {

std::vector<float> L2NormalizeTransform::Transform(
    const std::vector<float>& input) const {
  float squared_sum = 0.0F;
  for (float value : input) {
    squared_sum += value * value;
  }

  const float norm = std::sqrt(squared_sum);
  std::vector<float> output;
  output.reserve(input.size());
  for (float value : input) {
    output.push_back(value / norm);
  }
  return output;
}

}  // namespace nitr::case007
