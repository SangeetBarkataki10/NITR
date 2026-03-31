#include "policy.h"

namespace nitr::case004 {

Decision DecideEssential(const Metrics& m) {
  // Spec thresholds (M3 in your earlier milestones; you can bake into options later)
  if (m.num_inliers >= 30 && m.inlier_ratio >= 0.25 &&
      m.median_sampson_error <= 1.0) {
    return Decision::kAccept;
  }
  return Decision::kReject;
}

}  // namespace nitr::case004
