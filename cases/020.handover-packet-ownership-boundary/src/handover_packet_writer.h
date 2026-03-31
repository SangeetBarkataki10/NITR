#pragma once

#include <string>

#include "handover_packet.h"
#include "shift_tracker.h"

namespace nitr::case020 {

HandoverPacket SaveHandoverPacket(const ShiftTracker& tracker,
                                  const std::string& output_path);

}  // namespace nitr::case020
