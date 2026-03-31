#include <iostream>
#include <vector>

#include "inventory_report_service.h"
#include "summary_engine.h"

int main() {
  nitr::case012::BasicSummaryEngine engine;
  nitr::case012::InventoryReportService service(&engine);

  service.ReplaceProducts({
      {"A-100", 10, 3, 2.5},
      {"B-200", 2, 5, 10.0},
  });

  const nitr::case012::InventorySummary summary = service.GetSummary();
  std::cout << "products=" << summary.product_count
            << ", low_stock=" << summary.low_stock_count
            << ", value=" << summary.inventory_value << '\n';
  return 0;
}
