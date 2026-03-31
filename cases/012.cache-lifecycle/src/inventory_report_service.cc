#include "inventory_report_service.h"

#include <stdexcept>

namespace nitr::case012 {

InventoryReportService::InventoryReportService(const SummaryEngine* engine)
    : engine_(engine) {
  if (engine_ == nullptr) {
    throw std::invalid_argument("engine must not be null");
  }
}

void InventoryReportService::ReplaceProducts(
    const std::vector<Product>& products) {
  products_ = products;
}

void InventoryReportService::UpsertProduct(const Product& product) {
  for (Product& existing : products_) {
    if (existing.sku == product.sku) {
      existing = product;
      return;
    }
  }

  products_.push_back(product);
}

void InventoryReportService::ClearCache() {}

InventorySummary InventoryReportService::GetSummary() const {
  return engine_->Compute(products_);
}

}  // namespace nitr::case012
