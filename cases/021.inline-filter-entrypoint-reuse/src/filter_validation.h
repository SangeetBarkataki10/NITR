#ifndef FILTER_VALIDATION_H_
#define FILTER_VALIDATION_H_

#include <string>

#include "filter_rule.h"

namespace nitr::case021 {

enum class FilterErrorCode {
  kInvalidField,
  kInvalidOperator,
  kInvalidValue,
};

struct FilterError {
  FilterErrorCode code;
  std::string message;
};

bool ParseFieldName(const std::string& text, FilterField* field,
                    FilterError* error);
bool ParseOperatorToken(const std::string& text, FilterOperator* op,
                        FilterError* error);
bool ParseValueForField(FilterField field, FilterOperator op,
                        const std::string& text, FilterValue* value,
                        FilterError* error);

}  // namespace nitr::case021

#endif  // FILTER_VALIDATION_H_
