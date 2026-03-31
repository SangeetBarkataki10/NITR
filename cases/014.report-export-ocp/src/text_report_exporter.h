#ifndef TEXT_REPORT_EXPORTER_H_
#define TEXT_REPORT_EXPORTER_H_

#include "report_exporter.h"

namespace nitr::case014 {

class TextReportExporter : public ReportExporter {
 public:
  bool CanHandle(const std::string& format) const override;
  std::string Export(const Report& report) const override;
};

}  // namespace nitr::case014

#endif  // TEXT_REPORT_EXPORTER_H_
