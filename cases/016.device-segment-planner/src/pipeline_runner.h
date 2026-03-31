#pragma once

#include <string>
#include <vector>

#include "device_kind.h"
#include "pipeline_config.h"

namespace nitr::case016 {

struct StepExecution {
  std::string step_name;
  DeviceKind device;
};

struct PipelineRunResult {
  std::vector<StepExecution> executed_steps;
};

class PipelineRunner {
 public:
  PipelineRunResult Run(const PipelineConfig& config) const;
};

}  // namespace nitr::case016
