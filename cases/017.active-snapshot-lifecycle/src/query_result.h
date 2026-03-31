#ifndef CASE017_QUERY_RESULT_H_
#define CASE017_QUERY_RESULT_H_

#include <string>

namespace nitr::case017 {

enum class QueryStatus {
  kFound,
  kNotFound,
  kNoActiveSnapshot,
};

struct QueryResult {
  QueryStatus status;
  std::string value;
  std::string served_version;
};

}  // namespace nitr::case017

#endif  // CASE017_QUERY_RESULT_H_
