#ifndef REPORT_H_
#define REPORT_H_

#include <string>
#include <vector>

namespace nitr::case014 {

struct Report {
  std::string title;
  std::vector<std::string> columns;
  std::vector<std::vector<std::string>> rows;
};

}  // namespace nitr::case014

#endif  // REPORT_H_
