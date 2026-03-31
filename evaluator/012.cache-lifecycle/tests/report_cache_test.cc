#include <cassert>
#include <cmath>
#include <vector>

#include "inventory_report_service.h"
#include "summary_engine.h"

namespace {

class CountingSummaryEngine final : public nitr::case012::SummaryEngine {
 public:
  nitr::case012::InventorySummary Compute(
      const std::vector<nitr::case012::Product>& products) const override {
    compute_calls += 1;

    nitr::case012::InventorySummary summary;
    summary.product_count = static_cast<int>(products.size());
    for (const nitr::case012::Product& product : products) {
      if (product.units_in_stock <= product.reorder_threshold) {
        summary.low_stock_count += 1;
      }
      summary.inventory_value +=
          static_cast<double>(product.units_in_stock) * product.unit_price;
    }
    return summary;
  }

  mutable int compute_calls = 0;
};

bool NearlyEqual(double a, double b) {
  return std::fabs(a - b) < 1e-9;
}

void TestGetSummaryCachesRepeatedRead() {
  CountingSummaryEngine engine;
  nitr::case012::InventoryReportService service(&engine);

  service.ReplaceProducts({
      {"A-100", 10, 3, 2.5},
      {"B-200", 2, 5, 10.0},
  });

  const nitr::case012::InventorySummary first = service.GetSummary();
  const nitr::case012::InventorySummary second = service.GetSummary();

  assert(engine.compute_calls == 1);
  assert(first.product_count == 2);
  assert(first.low_stock_count == 1);
  assert(NearlyEqual(first.inventory_value, 45.0));
  assert(second.product_count == first.product_count);
  assert(second.low_stock_count == first.low_stock_count);
  assert(NearlyEqual(second.inventory_value, first.inventory_value));
}

void TestReplaceProductsInvalidatesCache() {
  CountingSummaryEngine engine;
  nitr::case012::InventoryReportService service(&engine);

  service.ReplaceProducts({
      {"A-100", 10, 3, 2.5},
      {"B-200", 2, 5, 10.0},
  });
  (void)service.GetSummary();

  service.ReplaceProducts({
      {"C-300", 1, 2, 7.0},
  });
  const nitr::case012::InventorySummary summary = service.GetSummary();

  assert(engine.compute_calls == 2);
  assert(summary.product_count == 1);
  assert(summary.low_stock_count == 1);
  assert(NearlyEqual(summary.inventory_value, 7.0));
}

void TestUpsertProductInvalidatesCache() {
  CountingSummaryEngine engine;
  nitr::case012::InventoryReportService service(&engine);

  service.ReplaceProducts({
      {"A-100", 10, 3, 2.5},
      {"B-200", 2, 5, 10.0},
  });
  (void)service.GetSummary();

  service.UpsertProduct({"B-200", 8, 5, 10.0});
  const nitr::case012::InventorySummary summary = service.GetSummary();

  assert(engine.compute_calls == 2);
  assert(summary.product_count == 2);
  assert(summary.low_stock_count == 0);
  assert(NearlyEqual(summary.inventory_value, 105.0));
}

void TestClearCacheForcesRecompute() {
  CountingSummaryEngine engine;
  nitr::case012::InventoryReportService service(&engine);

  service.ReplaceProducts({
      {"A-100", 10, 3, 2.5},
      {"B-200", 2, 5, 10.0},
  });
  (void)service.GetSummary();
  service.ClearCache();
  (void)service.GetSummary();

  assert(engine.compute_calls == 2);
}

}  // namespace

int main() {
  TestGetSummaryCachesRepeatedRead();
  TestReplaceProductsInvalidatesCache();
  TestUpsertProductInvalidatesCache();
  TestClearCacheForcesRecompute();
  return 0;
}
