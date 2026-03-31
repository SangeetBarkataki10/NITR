#include <iostream>
#include <string>

#include "handover_packet_preview.h"
#include "handover_packet_writer.h"
#include "shift_tracker.h"

int main() {
  nitr::case020::ShiftTracker tracker("SHIFT-042");
  tracker.AddCompletedTote("TOTE-100", 4);
  tracker.AddCompletedTote("TOTE-101", 3);
  tracker.StartTote("TOTE-102");
  tracker.ScanPackagesIntoCurrentTote(2);

  const std::string output_path = "handover_packet.txt";

  std::cout << nitr::case020::BuildHandoverPacketPreview(tracker);

  const nitr::case020::HandoverPacket packet =
      nitr::case020::SaveHandoverPacket(tracker, output_path);
  std::cout << "Saved " << packet.rows.size() << " packet rows to "
            << output_path << "\n";

  return 0;
}
