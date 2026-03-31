#include "build_pipeline.h"

namespace nitr::case015 {

BuiltPipeline BuildPipeline(const PipelineConfig& config) {
  // TODO(case-015): The enrichment feature is not wired yet.
  // When the feature is implemented, concrete provider selection should remain
  // here (or in app/main.cc) instead of moving into PipelineRunner.
  return BuiltPipeline(config, nullptr);
}

}  // namespace nitr::case015
