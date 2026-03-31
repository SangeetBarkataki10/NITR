#pragma once

#include <string>

namespace nitr::case015 {

enum class PolicyMode {
  kStatic,
  kFile,
};

struct PipelineConfig {
  PolicyMode policy_mode = PolicyMode::kStatic;
  std::string policy_file_path;
  bool enable_policy_enrichment = false;
};

}  // namespace nitr::case015
