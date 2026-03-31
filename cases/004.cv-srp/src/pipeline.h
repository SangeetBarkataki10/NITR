#pragma once

#include "types.h"

namespace nitr::case004 {

struct RunOutput {
  ErrorCode code = ErrorCode::kOk;
  std::optional<EstimationOutput> est;
  std::optional<Metrics> metrics;
  std::optional<Decision> decision;
};

RunOutput RunPipeline(const PairInput& in);

}  // namespace nitr::case004
