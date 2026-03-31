#include "pipeline.h"

#include "estimator.h"
#include "normalize.h"
#include "policy.h"
#include "scoring.h"
#include "types.h"

namespace nitr::case004 {

RunOutput RunPipeline(const PairInput& in) {
  RunOutput out;
  out.code = ErrorCode::kEstimationFailed;  // TODO(SRP): implement pipeline.
  return out;
}

}  // namespace nitr::case004
