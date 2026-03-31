#ifndef CASE017_SNAPSHOT_H_
#define CASE017_SNAPSHOT_H_

#include <string>
#include <unordered_map>

namespace nitr::case017 {

struct Snapshot {
  std::string version;
  std::unordered_map<std::string, std::string> data;
};

}  // namespace nitr::case017

#endif  // CASE017_SNAPSHOT_H_
