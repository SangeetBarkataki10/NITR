#ifndef CASE019_RANKER_H_
#define CASE019_RANKER_H_

#include <vector>

#include "item.h"
#include "ranking_result.h"

namespace nitr::case019 {

class Ranker {
 public:
  std::vector<RankedItem> Rank(const std::vector<Item>& items) const;

 private:
  int ComputeScore(const Item& item) const;
};

}  // namespace nitr::case019

#endif  // CASE019_RANKER_H_
