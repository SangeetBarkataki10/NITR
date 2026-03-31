#include "snapshot_store.h"

#include <utility>

namespace nitr::case017 {

bool SnapshotStore::RegisterSnapshot(
    const std::string& version,
    std::unordered_map<std::string, std::string> data) {
  if (version.empty()) {
    return false;
  }

  // Baseline behavior: overwrite if version already exists.
  snapshots_[version] = Snapshot{version, std::move(data)};

  // Baseline convenience: first successful registration becomes active.
  if (!has_active_) {
    has_active_ = true;
    active_version_ = version;
  }
  return true;
}

bool SnapshotStore::ActivateSnapshot(const std::string& version) {
  if (snapshots_.find(version) == snapshots_.end()) {
    return false;
  }

  has_active_ = true;
  active_version_ = version;
  return true;
}

void SnapshotStore::ResetActiveSnapshot() {
  has_active_ = false;
}

const Snapshot* SnapshotStore::GetActiveSnapshot() const {
  if (!has_active_) {
    return nullptr;
  }

  const auto it = snapshots_.find(active_version_);
  if (it == snapshots_.end()) {
    return nullptr;
  }
  return &it->second;
}

std::string SnapshotStore::GetActiveVersion() const {
  if (!has_active_) {
    return "";
  }
  return active_version_;
}

}  // namespace nitr::case017
