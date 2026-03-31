#include "file_policy_provider.h"

#include <fstream>
#include <regex>
#include <sstream>

namespace nitr::case015 {

FilePolicyProvider::FilePolicyProvider(std::string policy_file_path)
    : policy_file_path_(std::move(policy_file_path)) {
  Load();
}

Policy FilePolicyProvider::Lookup(const std::string& source_id) const {
  const auto it = policies_.find(source_id);
  if (it == policies_.end()) {
    return Policy::Fallback();
  }
  return it->second;
}

void FilePolicyProvider::Load() {
  std::ifstream input(policy_file_path_);
  if (!input.is_open()) {
    loaded_ = false;
    return;
  }

  std::ostringstream buffer;
  buffer << input.rdbuf();
  const std::string content = buffer.str();

  const std::regex entry_re(
      R"json("([^"]+)"\s*:\s*\{\s*"policy_tier"\s*:\s*"([^"]+)"\s*,\s*"retention_days"\s*:\s*(\d+)\s*\})json");

  for (std::sregex_iterator it(content.begin(), content.end(), entry_re), end;
       it != end; ++it) {
    policies_.emplace((*it)[1].str(),
                      Policy{(*it)[2].str(), std::stoi((*it)[3].str())});
  }

  loaded_ = !policies_.empty();
}

}  // namespace nitr::case015
