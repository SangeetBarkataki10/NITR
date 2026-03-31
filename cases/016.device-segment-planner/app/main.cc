#include <iostream>
#include <stdexcept>

#include "pipeline_config.h"
#include "pipeline_runner.h"

using nitr::case016::PipelineConfig;
using nitr::case016::PipelineRunner;
using nitr::case016::ToString;

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: device_segment_planner <config.json>\n";
    return 1;
  }

  try {
    const PipelineConfig config = PipelineConfig::FromJsonFile(argv[1]);
    const PipelineRunner runner;
    const auto result = runner.Run(config);
    for (const auto& step : result.executed_steps) {
      std::cout << step.step_name << ":" << ToString(step.device) << "\n";
    }
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << "\n";
    return 1;
  }
}
