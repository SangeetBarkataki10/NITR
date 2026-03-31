#pragma once

#include <string>

#include "shift_tracker.h"

namespace nitr::case020 {

std::string BuildHandoverPacketPreview(const ShiftTracker& tracker);

}  // namespace nitr::case020
