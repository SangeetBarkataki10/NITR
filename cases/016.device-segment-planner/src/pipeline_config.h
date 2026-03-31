#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include "device_kind.h"

namespace nitr::case016 {

struct StepConfig {
  std::string name;
  std::optional<DeviceKind> required_device;
};

class PipelineConfig {
 public:
  PipelineConfig();
  explicit PipelineConfig(
      std::vector<StepConfig> steps,
      std::optional<int> legacy_gpu_through_step = std::nullopt);

  static PipelineConfig FromJsonText(const std::string& json_text);
  static PipelineConfig FromJsonFile(const std::string& path);

  const std::vector<StepConfig>& steps() const;
  std::optional<int> legacy_gpu_through_step() const;
  std::size_t step_count() const;

 private:
  std::vector<StepConfig> steps_;
  std::optional<int> legacy_gpu_through_step_;
};

}  // namespace nitr::case016
