#ifndef NITR_INVENTORY_REPORT_SERVICE_H_
#define NITR_INVENTORY_REPORT_SERVICE_H_

#include <vector>

#include "product.h"
#include "summary_engine.h"

namespace nitr::case012 {

class InventoryReportService {
 public:
  explicit InventoryReportService(const SummaryEngine* engine);

  void ReplaceProducts(const std::vector<Product>& products);
  void UpsertProduct(const Product& product);
  void ClearCache();

  InventorySummary GetSummary() const;

 private:
  const SummaryEngine* engine_;
  std::vector<Product> products_;
};

}  // namespace nitr::case012

#endif  // NITR_INVENTORY_REPORT_SERVICE_H_
