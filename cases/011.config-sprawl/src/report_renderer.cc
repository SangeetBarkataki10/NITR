#include "report_renderer.h"

#include <sstream>

namespace nitr::case011 {
namespace {

std::string RenderHeader(const std::vector<Item>& items) {
  std::ostringstream out;
  out << "Inventory Report\n";
  out << "Items: " << items.size() << "\n";
  return out.str();
}

std::string RenderRow(const Item& item) {
  std::ostringstream out;
  out << "- id=" << item.id << ", name=" << item.name
      << ", qty=" << item.quantity << "\n";
  return out.str();
}

int TotalQuantity(const std::vector<Item>& items) {
  int total = 0;
  for (const Item& item : items) {
    total += item.quantity;
  }
  return total;
}

std::string RenderFooter(const std::vector<Item>& items,
                         const ReportOptions& options) {
  if (!options.include_summary) {
    return std::string();
  }

  std::ostringstream out;
  out << "Summary\n";
  out << "Total quantity: " << TotalQuantity(items) << "\n";
  return out.str();
}

}  // namespace

std::string RenderInventoryReport(const std::vector<Item>& items,
                                  const ReportOptions& options) {
  std::ostringstream out;
  out << RenderHeader(items);
  for (const Item& item : items) {
    out << RenderRow(item);
  }
  out << RenderFooter(items, options);
  return out.str();
}

}  // namespace nitr::case011
