#ifndef REPORT_EXPORTER_H_
#define REPORT_EXPORTER_H_

#include <string>

#include "report.h"

namespace nitr::case014 {

class ReportExporter {
 public:
  virtual ~ReportExporter() = default;

  virtual bool CanHandle(const std::string& format) const = 0;
  virtual std::string Export(const Report& report) const = 0;
};

}  // namespace nitr::case014

#endif  // REPORT_EXPORTER_H_
