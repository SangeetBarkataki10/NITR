#include "query_service.h"

namespace nitr::case017 {

QueryService::QueryService(const SnapshotStore& store) : store_(store) {}

void QueryService::BindActiveSnapshot() {
  bound_snapshot_ = store_.GetActiveSnapshot();
}

QueryResult QueryService::Lookup(const std::string& key) const {
  if (bound_snapshot_ == nullptr) {
    return QueryResult{QueryStatus::kNoActiveSnapshot, "", ""};
  }

  const auto it = bound_snapshot_->data.find(key);
  if (it == bound_snapshot_->data.end()) {
    return QueryResult{QueryStatus::kNotFound, "", bound_snapshot_->version};
  }

  return QueryResult{QueryStatus::kFound, it->second, bound_snapshot_->version};
}

}  // namespace nitr::case017
