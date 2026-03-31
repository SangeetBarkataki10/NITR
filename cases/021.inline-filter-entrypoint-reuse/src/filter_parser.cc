#include "filter_parser.h"

#include <string>

namespace {

nitr::case021::FilterRule MakeEmptyRule() {
  nitr::case021::FilterValue value;
  value.kind = nitr::case021::FilterValueKind::kText;
  value.text = "";
  value.number = 0;

  nitr::case021::FilterRule rule;
  rule.field = nitr::case021::FilterField::kStatus;
  rule.op = nitr::case021::FilterOperator::kEquals;
  rule.value = value;
  return rule;
}

}  // namespace

namespace nitr::case021 {

FilterParseResult ParseFilterClause(const FilterClause& clause) {
  FilterParseResult result;
  result.ok = false;
  result.rule = MakeEmptyRule();
  result.error = FilterError{FilterErrorCode::kInvalidField, ""};

  FilterField field;
  if (!ParseFieldName(clause.field, &field, &result.error)) {
    return result;
  }

  FilterOperator op;
  if (!ParseOperatorToken(clause.op, &op, &result.error)) {
    return result;
  }

  FilterValue value;
  if (!ParseValueForField(field, op, clause.value, &value, &result.error)) {
    return result;
  }

  result.ok = true;
  result.rule.field = field;
  result.rule.op = op;
  result.rule.value = value;
  result.error = FilterError{FilterErrorCode::kInvalidField, ""};
  return result;
}

FilterParseResult ParseInlineFilter(const std::string& text) {
  FilterParseResult result;
  result.ok = false;
  result.rule = MakeEmptyRule();
  result.error = FilterError{FilterErrorCode::kInvalidOperator, text};
  return result;
}

}  // namespace nitr::case021
