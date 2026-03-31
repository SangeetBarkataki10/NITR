#ifndef NEEDLE_REPORT_RENDERER_H_
#define NEEDLE_REPORT_RENDERER_H_

#include <string>
#include <vector>

#include "report_types.h"

namespace nitr::case011 {

std::string RenderInventoryReport(const std::vector<Item>& items,
                                  const ReportOptions& options);

}  // namespace nitr::case011

#endif  // NEEDLE_REPORT_RENDERER_H_
