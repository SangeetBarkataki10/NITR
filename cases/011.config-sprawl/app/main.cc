#include <iostream>

#include "report_renderer.h"
#include "report_types.h"

int main() {
  const std::vector<nitr::case011::Item> items = nitr::case011::SampleItems();

  nitr::case011::ReportOptions full_options;
  full_options.include_summary = true;

  std::cout << "=== Full Report ===\n";
  std::cout << nitr::case011::RenderInventoryReport(items, full_options)
            << "\n";

  std::cout << "=== Compact Report ===\n";
  std::cout << "Compact mode not implemented yet.\n";

  return 0;
}
