#ifndef CASE017_SNAPSHOT_STORE_H_
#define CASE017_SNAPSHOT_STORE_H_

#include <string>
#include <unordered_map>

#include "snapshot.h"

namespace nitr::case017 {

class SnapshotStore {
 public:
  bool RegisterSnapshot(const std::string& version,
                        std::unordered_map<std::string, std::string> data);

  bool ActivateSnapshot(const std::string& version);
  void ResetActiveSnapshot();

  const Snapshot* GetActiveSnapshot() const;
  std::string GetActiveVersion() const;

 private:
  std::unordered_map<std::string, Snapshot> snapshots_;
  std::string active_version_;
  bool has_active_ = false;
};

}  // namespace nitr::case017

#endif  // CASE017_SNAPSHOT_STORE_H_
