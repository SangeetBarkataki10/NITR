#include <iostream>
#include <unordered_map>

#include "query_service.h"
#include "snapshot_store.h"

namespace {

void PrintLookup(const nitr::case017::QueryResult& result,
                 const std::string& key) {
  std::cout << "lookup(" << key << ") -> ";
  switch (result.status) {
    case nitr::case017::QueryStatus::kFound:
      std::cout << "found value='" << result.value << "' from "
                << result.served_version << "\n";
      break;
    case nitr::case017::QueryStatus::kNotFound:
      std::cout << "missing key in " << result.served_version << "\n";
      break;
    case nitr::case017::QueryStatus::kNoActiveSnapshot:
      std::cout << "no active snapshot\n";
      break;
  }
}

}  // namespace

int main() {
  nitr::case017::SnapshotStore store;

  store.RegisterSnapshot("v1", {{"name", "alpha"}, {"color", "blue"}});
  store.RegisterSnapshot("v2", {{"name", "beta"}, {"color", "green"}});

  nitr::case017::QueryService query(store);
  query.BindActiveSnapshot();

  PrintLookup(query.Lookup("name"), "name");

  store.ActivateSnapshot("v2");
  query.BindActiveSnapshot();
  PrintLookup(query.Lookup("name"), "name");

  store.ResetActiveSnapshot();
  query.BindActiveSnapshot();
  PrintLookup(query.Lookup("name"), "name");

  return 0;
}
