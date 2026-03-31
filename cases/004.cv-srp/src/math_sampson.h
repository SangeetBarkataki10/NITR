#pragma once

#include "math_linalg.h"
#include "types.h"

namespace nitr::case004 {

double SampsonErrorSq(const Mat3& E, double x0, double y0, double x1,
                      double y1);

static inline double MedianOfSorted(std::vector<double>* v_sorted) {
  const size_t n = v_sorted->size();
  if (n == 0) {
    return std::numeric_limits<double>::infinity();
  }
  const size_t mid = n / 2;
  if ((n % 2) == 1) {
    return (*v_sorted)[mid];
  }
  return 0.5 * ((*v_sorted)[mid - 1] + (*v_sorted)[mid]);
}

double MedianSampsonError(const NormalizedPair& norm, const Model& E_model,
                          const std::vector<bool>& inliers);

}  // namespace nitr::case004
