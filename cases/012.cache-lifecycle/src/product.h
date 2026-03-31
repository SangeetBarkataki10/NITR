#ifndef NITR_PRODUCT_H_
#define NITR_PRODUCT_H_

#include <string>

namespace nitr::case012 {

struct Product {
  std::string sku;
  int units_in_stock = 0;
  int reorder_threshold = 0;
  double unit_price = 0.0;
};

}  // namespace nitr::case012

#endif  // NITR_PRODUCT_H_
