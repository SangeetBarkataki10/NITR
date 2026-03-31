#ifndef FILTER_PARSER_H_
#define FILTER_PARSER_H_

#include <string>

#include "filter_clause.h"
#include "filter_validation.h"

namespace nitr::case021 {

struct FilterParseResult {
  bool ok;
  FilterRule rule;
  FilterError error;
};

FilterParseResult ParseFilterClause(const FilterClause& clause);
FilterParseResult ParseInlineFilter(const std::string& text);

}  // namespace nitr::case021

#endif  // FILTER_PARSER_H_
