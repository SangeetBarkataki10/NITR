#ifndef CASE019_ITEM_H_
#define CASE019_ITEM_H_

#include <string>

namespace nitr::case019 {

struct Item {
  int id;
  std::string name;
  int base_score;
  bool category_match;
  int freshness_days;
  int popularity;
  bool is_blocked;
};

}  // namespace nitr::case019

#endif  // CASE019_ITEM_H_
