#include "execution_plan.h"

namespace nitr::case016 {

ExecutionPlan BuildExecutionPlan(const PipelineConfig& config) {
  if (config.step_count() == 0U) {
    return {};
  }

  return {{DeviceKind::kGpu, 0U, config.step_count() - 1U}};
}

}  // namespace nitr::case016
