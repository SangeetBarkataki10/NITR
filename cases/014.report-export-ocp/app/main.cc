#include <iostream>

#include "exporter_factory.h"
#include "report_export_service.h"

int main() {
  nitr::case014::Report report;
  report.title = "Quarterly Metrics";
  report.columns = {"Name", "Value"};
  report.rows = {{"Latency", "120ms"}, {"Errors", "3"}};

  nitr::case014::ReportExportService service(
      nitr::case014::CreateDefaultExporters());

  try {
    std::cout << service.ExportReport(report, "text");
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}
