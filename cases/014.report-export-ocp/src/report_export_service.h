#ifndef REPORT_EXPORT_SERVICE_H_
#define REPORT_EXPORT_SERVICE_H_

#include <memory>
#include <string>
#include <vector>

#include "report_exporter.h"

namespace nitr::case014 {

class ReportExportService {
 public:
  explicit ReportExportService(
      std::vector<std::unique_ptr<ReportExporter>> exporters);

  std::string ExportReport(const Report& report,
                           const std::string& format) const;

 private:
  std::vector<std::unique_ptr<ReportExporter>> exporters_;
};

}  // namespace nitr::case014

#endif  // REPORT_EXPORT_SERVICE_H_
