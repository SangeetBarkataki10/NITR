#include "handover_packet.h"

#include <sstream>

namespace nitr::case020 {

std::string RenderPacketText(const HandoverPacket& packet) {
  std::ostringstream output;
  output << "Handover packet for shift " << packet.shift_id << "\n";
  output << "Rows:\n";

  for (const HandoverPacketRow& row : packet.rows) {
    output << "  " << row.row_number << ". " << row.tote_id
           << " packages=" << row.package_count;
    if (row.from_in_progress_tote) {
      output << " [in-progress]";
    }
    output << "\n";
  }

  output << "Summary: totes=" << packet.summary.tote_count
         << ", packages=" << packet.summary.package_count << "\n";
  return output.str();
}

}  // namespace nitr::case020
