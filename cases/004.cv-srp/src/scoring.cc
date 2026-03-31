#include "scoring.h"

#include "math_sampson.h"

namespace nitr::case004 {

Metrics ScoreEssential(const PairInput& in, const NormalizedPair& norm,
                       const EstimationOutput& est) {
  Metrics m;
  m.num_matches = static_cast<int>(in.matches.size());
  m.num_inliers = 0;
  for (bool b : est.inliers) {
    if (b) {
      m.num_inliers++;
    }
  }
  m.inlier_ratio =
      (m.num_matches > 0) ? (double(m.num_inliers) / m.num_matches) : 0.0;
  m.median_sampson_error = MedianSampsonError(norm, est.model, est.inliers);
  return m;
}

}  // namespace nitr::case004
