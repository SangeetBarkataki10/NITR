#include "filter_rule.h"

#include <sstream>

namespace nitr::case021 {

std::string ToString(FilterField field) {
  switch (field) {
    case FilterField::kStatus:
      return "status";
    case FilterField::kPriority:
      return "priority";
    case FilterField::kOwner:
      return "owner";
  }

  return "unknown";
}

std::string ToString(FilterOperator op) {
  switch (op) {
    case FilterOperator::kEquals:
      return "=";
    case FilterOperator::kGreaterEqual:
      return ">=";
    case FilterOperator::kContains:
      return ":";
  }

  return "?";
}

std::string ToString(const FilterValue& value) {
  if (value.kind == FilterValueKind::kInteger) {
    return std::to_string(value.number);
  }

  return value.text;
}

std::string ToString(const FilterRule& rule) {
  std::ostringstream out;
  out << ToString(rule.field) << " " << ToString(rule.op) << " "
      << ToString(rule.value);
  return out.str();
}

}  // namespace nitr::case021
