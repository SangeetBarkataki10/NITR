#include "exporter_factory.h"

#include <memory>
#include <vector>

#include "csv_report_exporter.h"
#include "text_report_exporter.h"

namespace nitr::case014 {

std::vector<std::unique_ptr<ReportExporter>> CreateDefaultExporters() {
  std::vector<std::unique_ptr<ReportExporter>> exporters;
  exporters.push_back(std::make_unique<TextReportExporter>());
  exporters.push_back(std::make_unique<CsvReportExporter>());
  return exporters;
}

}  // namespace nitr::case014
