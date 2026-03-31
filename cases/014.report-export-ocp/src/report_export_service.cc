#include "report_export_service.h"

#include <stdexcept>

namespace nitr::case014 {

ReportExportService::ReportExportService(
    std::vector<std::unique_ptr<ReportExporter>> exporters)
    : exporters_(std::move(exporters)) {}

std::string ReportExportService::ExportReport(const Report& report,
                                              const std::string& format) const {
  for (const auto& exporter : exporters_) {
    if (exporter->CanHandle(format)) {
      return exporter->Export(report);
    }
  }
  throw std::invalid_argument("Unsupported format: " + format);
}

}  // namespace nitr::case014
