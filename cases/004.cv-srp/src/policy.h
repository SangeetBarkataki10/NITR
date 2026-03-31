#pragma once

#include "types.h"

namespace nitr::case004 {

// SRP: policy consumes metrics only, returns accept/reject.
Decision DecideEssential(const Metrics& m);

}  // namespace nitr::case004
