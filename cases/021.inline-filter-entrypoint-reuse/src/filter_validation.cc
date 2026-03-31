#include "filter_validation.h"

#include <cctype>
#include <string>

namespace {

std::string Trim(std::string text) {
  std::size_t start = 0;
  while (start < text.size() &&
         std::isspace(static_cast<unsigned char>(text[start])) != 0) {
    ++start;
  }

  std::size_t end = text.size();
  while (end > start &&
         std::isspace(static_cast<unsigned char>(text[end - 1])) != 0) {
    --end;
  }

  return text.substr(start, end - start);
}

nitr::case021::FilterError MakeError(nitr::case021::FilterErrorCode code,
                                     const std::string& detail) {
  switch (code) {
    case nitr::case021::FilterErrorCode::kInvalidField:
      return nitr::case021::FilterError{code, "invalid field: " + detail};
    case nitr::case021::FilterErrorCode::kInvalidOperator:
      return nitr::case021::FilterError{code, "invalid operator: " + detail};
    case nitr::case021::FilterErrorCode::kInvalidValue:
      return nitr::case021::FilterError{code, "invalid value: " + detail};
  }

  return nitr::case021::FilterError{code, detail};
}

bool IsInteger(const std::string& text) {
  if (text.empty()) {
    return false;
  }

  for (char ch : text) {
    if (std::isdigit(static_cast<unsigned char>(ch)) == 0) {
      return false;
    }
  }

  return true;
}

}  // namespace

namespace nitr::case021 {

bool ParseFieldName(const std::string& text, FilterField* field,
                    FilterError* error) {
  const std::string normalized = Trim(text);
  if (normalized == "status") {
    *field = FilterField::kStatus;
    return true;
  }

  if (normalized == "priority") {
    *field = FilterField::kPriority;
    return true;
  }

  if (normalized == "owner") {
    *field = FilterField::kOwner;
    return true;
  }

  *error = MakeError(FilterErrorCode::kInvalidField, normalized);
  return false;
}

bool ParseOperatorToken(const std::string& text, FilterOperator* op,
                        FilterError* error) {
  const std::string normalized = Trim(text);
  if (normalized == "=") {
    *op = FilterOperator::kEquals;
    return true;
  }

  if (normalized == ">=") {
    *op = FilterOperator::kGreaterEqual;
    return true;
  }

  if (normalized == ":") {
    *op = FilterOperator::kContains;
    return true;
  }

  *error = MakeError(FilterErrorCode::kInvalidOperator, normalized);
  return false;
}

bool ParseValueForField(FilterField field, FilterOperator op,
                        const std::string& text, FilterValue* value,
                        FilterError* error) {
  const std::string normalized = Trim(text);
  if (normalized.empty()) {
    *error = MakeError(FilterErrorCode::kInvalidValue, normalized);
    return false;
  }

  if (field == FilterField::kPriority) {
    if (op == FilterOperator::kContains) {
      *error = MakeError(FilterErrorCode::kInvalidOperator, ToString(op));
      return false;
    }

    if (!IsInteger(normalized)) {
      *error = MakeError(FilterErrorCode::kInvalidValue, normalized);
      return false;
    }

    value->kind = FilterValueKind::kInteger;
    value->text = normalized;
    value->number = std::stoi(normalized);
    return true;
  }

  if (op == FilterOperator::kGreaterEqual) {
    *error = MakeError(FilterErrorCode::kInvalidOperator, ToString(op));
    return false;
  }

  value->kind = FilterValueKind::kText;
  value->text = normalized;
  value->number = 0;
  return true;
}

}  // namespace nitr::case021
