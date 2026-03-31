#include "handover_packet_writer.h"

#include <fstream>
#include <stdexcept>

namespace nitr::case020 {

HandoverPacket SaveHandoverPacket(const ShiftTracker& tracker,
                                  const std::string& output_path) {
  HandoverPacket packet;
  packet.shift_id = tracker.shift_id();

  int next_row_number = 1;
  int total_packages = 0;

  for (const ToteRecord& tote : tracker.completed_totes()) {
    packet.rows.push_back(HandoverPacketRow{
        next_row_number,
        tote.tote_id,
        tote.package_count,
        false,
    });
    total_packages += tote.package_count;
    ++next_row_number;
  }

  if (tracker.current_tote().has_value()) {
    const ToteRecord& current_tote = *tracker.current_tote();
    packet.rows.push_back(HandoverPacketRow{
        next_row_number,
        current_tote.tote_id,
        current_tote.package_count,
        true,
    });
    total_packages += current_tote.package_count;
  }

  packet.summary = HandoverPacketSummary{
      static_cast<int>(packet.rows.size()),
      total_packages,
  };

  std::ofstream output(output_path);
  if (!output) {
    throw std::runtime_error("failed to open output path");
  }

  output << RenderPacketText(packet);
  if (!output) {
    throw std::runtime_error("failed to write handover packet");
  }

  return packet;
}

}  // namespace nitr::case020
