#pragma once

#include <string>
#include <vector>

namespace nitr::case020 {

struct HandoverPacketRow {
  int row_number;
  std::string tote_id;
  int package_count;
  bool from_in_progress_tote;
};

struct HandoverPacketSummary {
  int tote_count;
  int package_count;
};

struct HandoverPacket {
  std::string shift_id;
  std::vector<HandoverPacketRow> rows;
  HandoverPacketSummary summary;
};

std::string RenderPacketText(const HandoverPacket& packet);

}  // namespace nitr::case020
