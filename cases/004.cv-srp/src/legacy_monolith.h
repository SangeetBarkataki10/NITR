#pragma once

#include <string>

#include "types.h"

namespace nitr::case004 {

// The harness may call this to compare behavior.
// SRP pipeline must NOT call it.
ErrorCode RunLegacyMonolith(const std::string& input_path,
                            const std::string& output_path);

}  // namespace nitr::case004
