#include <iostream>

#include "filter_clause.h"
#include "filter_parser.h"
#include "filter_rule.h"

int main() {
  const nitr::case021::FilterClause clause{"priority", ">=", "3"};
  const nitr::case021::FilterParseResult result =
      nitr::case021::ParseFilterClause(clause);

  if (!result.ok) {
    std::cerr << result.error.message << "\n";
    return 1;
  }

  std::cout << nitr::case021::ToString(result.rule) << "\n";
  return 0;
}
