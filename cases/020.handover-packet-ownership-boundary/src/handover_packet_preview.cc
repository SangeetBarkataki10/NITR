#include "handover_packet_preview.h"

#include <sstream>

namespace nitr::case020 {

std::string BuildHandoverPacketPreview(const ShiftTracker& tracker) {
  std::ostringstream output;
  output << "Preview for shift " << tracker.shift_id()
         << " is not available yet.\n";
  output << "Use the saved handover packet for now.\n";
  return output.str();
}

}  // namespace nitr::case020
