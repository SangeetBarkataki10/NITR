#ifndef FILTER_CLAUSE_H_
#define FILTER_CLAUSE_H_

#include <string>

namespace nitr::case021 {

struct FilterClause {
  std::string field;
  std::string op;
  std::string value;
};

}  // namespace nitr::case021

#endif  // FILTER_CLAUSE_H_
