#pragma once

#include <optional>
#include <string>

#include "types.h"

namespace nitr::case004 {

struct ParseOutput {
  std::optional<PairInput> input;
  ErrorCode err = ErrorCode::kOk;
};

// Parser owns schema validation.
ParseOutput ParsePairJsonFromFile(const std::string& path);

// Serializer writes final result.json.
// (SRP: serializer depends on domain types only; pipeline provides filled Result.)
ErrorCode WriteResultJsonToFile(const std::string& path, const PairInput& in,
                                const EstimationOutput& est, const Metrics& m,
                                Decision d);

}  // namespace nitr::case004
