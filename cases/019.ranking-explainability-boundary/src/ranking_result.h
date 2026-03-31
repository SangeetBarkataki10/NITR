#ifndef CASE019_RANKING_RESULT_H_
#define CASE019_RANKING_RESULT_H_

#include "item.h"

namespace nitr::case019 {

struct RankedItem {
  Item item;
  int final_score;
};

}  // namespace nitr::case019

#endif  // CASE019_RANKING_RESULT_H_
