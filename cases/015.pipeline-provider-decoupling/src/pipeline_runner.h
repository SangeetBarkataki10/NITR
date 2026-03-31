#pragma once

#include <string>
#include <vector>

#include "event.h"
#include "pipeline_config.h"

namespace nitr::case015 {

class PolicyProvider;

class PipelineRunner {
 public:
  PipelineRunner(PipelineConfig config, const PolicyProvider* policy_provider);

  std::vector<std::string> Run(const std::vector<Event>& events) const;

 private:
  static std::string NormalizePayload(const std::string& payload);

  PipelineConfig config_;
  const PolicyProvider* policy_provider_;
};

}  // namespace nitr::case015
