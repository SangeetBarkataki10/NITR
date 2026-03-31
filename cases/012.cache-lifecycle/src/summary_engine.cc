#include "summary_engine.h"

namespace nitr::case012 {

InventorySummary BasicSummaryEngine::Compute(
    const std::vector<Product>& products) const {
  InventorySummary summary;
  summary.product_count = static_cast<int>(products.size());

  for (const Product& product : products) {
    if (product.units_in_stock <= product.reorder_threshold) {
      summary.low_stock_count += 1;
    }
    summary.inventory_value +=
        static_cast<double>(product.units_in_stock) * product.unit_price;
  }

  return summary;
}

}  // namespace nitr::case012
