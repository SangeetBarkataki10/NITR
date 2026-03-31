#ifndef NITR_SUMMARY_ENGINE_H_
#define NITR_SUMMARY_ENGINE_H_

#include <vector>

#include "product.h"

namespace nitr::case012 {

struct InventorySummary {
  int product_count = 0;
  int low_stock_count = 0;
  double inventory_value = 0.0;
};

class SummaryEngine {
 public:
  virtual ~SummaryEngine() = default;
  virtual InventorySummary Compute(
      const std::vector<Product>& products) const = 0;
};

class BasicSummaryEngine final : public SummaryEngine {
 public:
  InventorySummary Compute(const std::vector<Product>& products) const override;
};

}  // namespace nitr::case012

#endif  // NITR_SUMMARY_ENGINE_H_
