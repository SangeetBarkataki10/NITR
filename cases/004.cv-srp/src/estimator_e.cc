#include "estimator.h"

namespace nitr::case004 {

std::optional<EstimationOutput> EssentialEstimator::Estimate(
    const PairInput& in, const NormalizedPair& norm) const {
  // TODO: implement RANSAC + 5pt/8pt + Sampson scoring.
  // Temporary stub: fail if not enough matches.
  if (norm.x0.size() < 8) {
    return std::nullopt;
  }

  EstimationOutput out;
  out.model.type = "E";
  // Identity-like placeholder (NOT a valid E; just to make pipeline compile)
  out.model.mat3x3 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  out.inliers.assign(norm.x0.size(), true);
  return out;
}

}  // namespace nitr::case004
