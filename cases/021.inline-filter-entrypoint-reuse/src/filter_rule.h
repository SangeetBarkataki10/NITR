#ifndef FILTER_RULE_H_
#define FILTER_RULE_H_

#include <string>

namespace nitr::case021 {

enum class FilterField {
  kStatus,
  kPriority,
  kOwner,
};

enum class FilterOperator {
  kEquals,
  kGreaterEqual,
  kContains,
};

enum class FilterValueKind {
  kText,
  kInteger,
};

struct FilterValue {
  FilterValueKind kind;
  std::string text;
  int number;
};

struct FilterRule {
  FilterField field;
  FilterOperator op;
  FilterValue value;
};

std::string ToString(FilterField field);
std::string ToString(FilterOperator op);
std::string ToString(const FilterValue& value);
std::string ToString(const FilterRule& rule);

}  // namespace nitr::case021

#endif  // FILTER_RULE_H_
