#include "pipeline_config.h"

#include <fstream>
#include <iterator>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace nitr::case016 {
namespace {

std::string ReadAll(const std::string& path) {
  std::ifstream input(path);
  if (!input.is_open()) {
    throw std::runtime_error("Could not open config file: " + path);
  }
  return std::string(std::istreambuf_iterator<char>(input),
                     std::istreambuf_iterator<char>());
}

std::optional<int> ExtractLegacyGpuThroughStep(const std::string& json_text) {
  const std::regex pattern("\"legacy_gpu_through_step\"\\s*:\\s*(\\d+)");
  std::smatch match;
  if (!std::regex_search(json_text, match, pattern)) {
    return std::nullopt;
  }
  return std::stoi(match[1].str());
}

std::vector<StepConfig> ExtractSteps(const std::string& json_text) {
  const std::regex step_pattern(
      "\\{\\s*\\\"name\\\"\\s*:\\s*\\\"([^\\\"]+)\\\"(?:\\s*,\\s*"
      "\\\"device\\\"\\s*:\\s*\\\"(cpu|gpu)\\\")?\\s*\\}");
  std::vector<StepConfig> steps;

  auto begin =
      std::sregex_iterator(json_text.begin(), json_text.end(), step_pattern);
  auto end = std::sregex_iterator();
  for (auto it = begin; it != end; ++it) {
    StepConfig step;
    step.name = (*it)[1].str();
    if ((*it)[2].matched) {
      step.required_device = DeviceKindFromString((*it)[2].str());
    }
    steps.push_back(step);
  }

  if (steps.empty()) {
    throw std::runtime_error("Config did not contain any steps.");
  }
  return steps;
}

}  // namespace

PipelineConfig::PipelineConfig() = default;

PipelineConfig::PipelineConfig(std::vector<StepConfig> steps,
                               const std::optional<int> legacy_gpu_through_step)
    : steps_(std::move(steps)),
      legacy_gpu_through_step_(legacy_gpu_through_step) {}

PipelineConfig PipelineConfig::FromJsonText(const std::string& json_text) {
  return PipelineConfig(ExtractSteps(json_text),
                        ExtractLegacyGpuThroughStep(json_text));
}

PipelineConfig PipelineConfig::FromJsonFile(const std::string& path) {
  return FromJsonText(ReadAll(path));
}

const std::vector<StepConfig>& PipelineConfig::steps() const {
  return steps_;
}

std::optional<int> PipelineConfig::legacy_gpu_through_step() const {
  return legacy_gpu_through_step_;
}

std::size_t PipelineConfig::step_count() const {
  return steps_.size();
}

}  // namespace nitr::case016
