#pragma once

#include <string>
#include <unordered_map>

#include "policy_provider.h"

namespace nitr::case015 {

class FilePolicyProvider : public PolicyProvider {
 public:
  explicit FilePolicyProvider(std::string policy_file_path);

  Policy Lookup(const std::string& source_id) const override;
  bool loaded() const {
    return loaded_;
  }

 private:
  void Load();

  std::string policy_file_path_;
  std::unordered_map<std::string, Policy> policies_;
  bool loaded_ = false;
};

}  // namespace nitr::case015
