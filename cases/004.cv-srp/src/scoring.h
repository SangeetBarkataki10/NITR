#pragma once

#include "types.h"

namespace nitr::case004 {

// SRP: scorer only computes metrics from inputs + estimation outputs.
Metrics ScoreEssential(const PairInput& in, const NormalizedPair& norm,
                       const EstimationOutput& est);

}  // namespace nitr::case004
