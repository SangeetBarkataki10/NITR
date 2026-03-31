#ifndef CASE017_QUERY_SERVICE_H_
#define CASE017_QUERY_SERVICE_H_

#include <string>

#include "query_result.h"
#include "snapshot.h"
#include "snapshot_store.h"

namespace nitr::case017 {

class QueryService {
 public:
  explicit QueryService(const SnapshotStore& store);

  // Baseline wiring binds once and keeps a local pointer.
  void BindActiveSnapshot();

  QueryResult Lookup(const std::string& key) const;

 private:
  const SnapshotStore& store_;
  const Snapshot* bound_snapshot_ = nullptr;
};

}  // namespace nitr::case017

#endif  // CASE017_QUERY_SERVICE_H_
