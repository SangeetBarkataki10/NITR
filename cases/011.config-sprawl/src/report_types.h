#ifndef NEEDLE_REPORT_TYPES_H_
#define NEEDLE_REPORT_TYPES_H_

#include <string>
#include <vector>

namespace nitr::case011 {

struct Item {
  std::string id;
  std::string name;
  int quantity = 0;
};

struct ReportOptions {
  bool include_summary = true;
  bool compact_mode = false;
};

std::vector<Item> SampleItems();

}  // namespace nitr::case011

#endif  // NEEDLE_REPORT_TYPES_H_
