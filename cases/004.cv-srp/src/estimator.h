#pragma once

#include <optional>

#include "types.h"

namespace nitr::case004 {

// SRP: estimator only estimates model + inliers.
class EssentialEstimator {
 public:
  std::optional<EstimationOutput> Estimate(const PairInput& in,
                                           const NormalizedPair& norm) const;
};

}  // namespace nitr::case004
