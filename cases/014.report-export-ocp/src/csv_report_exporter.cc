#include "csv_report_exporter.h"

#include <sstream>

namespace nitr::case014 {

bool CsvReportExporter::CanHandle(const std::string& format) const {
  return format == "csv";
}

std::string CsvReportExporter::Export(const Report& report) const {
  std::ostringstream out;
  for (std::size_t i = 0; i < report.columns.size(); ++i) {
    if (i > 0) {
      out << ',';
    }
    out << report.columns[i];
  }
  out << "\n";
  for (const auto& row : report.rows) {
    for (std::size_t i = 0; i < row.size(); ++i) {
      if (i > 0) {
        out << ',';
      }
      out << row[i];
    }
    out << "\n";
  }
  return out.str();
}

}  // namespace nitr::case014
