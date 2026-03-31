#pragma once

#include <memory>

#include "pipeline_config.h"
#include "pipeline_runner.h"
#include "policy_provider.h"

namespace nitr::case015 {

struct BuiltPipeline {
  std::unique_ptr<PolicyProvider> policy_provider;
  PipelineRunner runner;

  BuiltPipeline(PipelineConfig config, std::unique_ptr<PolicyProvider> provider)
      : policy_provider(std::move(provider)),
        runner(config, policy_provider.get()) {}
};

BuiltPipeline BuildPipeline(const PipelineConfig& config);

}  // namespace nitr::case015
