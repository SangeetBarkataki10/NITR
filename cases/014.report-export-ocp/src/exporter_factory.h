#ifndef EXPORTER_FACTORY_H_
#define EXPORTER_FACTORY_H_

#include <memory>
#include <vector>

#include "report_exporter.h"

namespace nitr::case014 {

std::vector<std::unique_ptr<ReportExporter>> CreateDefaultExporters();

}  // namespace nitr::case014

#endif  // EXPORTER_FACTORY_H_
