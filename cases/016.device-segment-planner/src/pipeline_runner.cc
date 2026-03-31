#include "pipeline_runner.h"

namespace nitr::case016 {

PipelineRunResult PipelineRunner::Run(const PipelineConfig& config) const {
  PipelineRunResult result;
  result.executed_steps.reserve(config.steps().size());

  for (const StepConfig& step : config.steps()) {
    result.executed_steps.push_back({step.name, DeviceKind::kGpu});
  }

  return result;
}

}  // namespace nitr::case016
