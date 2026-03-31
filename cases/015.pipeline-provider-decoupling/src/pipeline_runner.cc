#include "pipeline_runner.h"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace nitr::case015 {

PipelineRunner::PipelineRunner(PipelineConfig config,
                               const PolicyProvider* policy_provider)
    : config_(std::move(config)), policy_provider_(policy_provider) {}

std::vector<std::string> PipelineRunner::Run(
    const std::vector<Event>& events) const {
  std::vector<std::string> output;
  output.reserve(events.size());

  for (const Event& event : events) {
    std::ostringstream line;
    line << "source=" << event.source_id
         << ";payload=" << NormalizePayload(event.payload)
         << ";score=" << event.score;

    // TODO(case-015): policy enrichment is intentionally not wired yet.
    // The future solution should add policy_tier and retention_days without
    // turning PipelineRunner into a provider-selection/composition layer.
    (void)config_;
    (void)policy_provider_;

    output.push_back(line.str());
  }

  return output;
}

std::string PipelineRunner::NormalizePayload(const std::string& payload) {
  std::string normalized = payload;
  std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                 [](unsigned char c) {
                   if (c == ' ') {
                     return static_cast<char>('_');
                   }
                   return static_cast<char>(std::toupper(c));
                 });
  return normalized;
}

}  // namespace nitr::case015
