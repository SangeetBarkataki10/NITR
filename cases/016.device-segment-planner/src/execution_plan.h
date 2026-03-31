#pragma once

#include <cstddef>
#include <vector>

#include "device_kind.h"
#include "pipeline_config.h"

namespace nitr::case016 {

struct DeviceSegment {
  DeviceKind device;
  std::size_t start_step_index;
  std::size_t end_step_index;
};

using ExecutionPlan = std::vector<DeviceSegment>;

ExecutionPlan BuildExecutionPlan(const PipelineConfig& config);

}  // namespace nitr::case016
