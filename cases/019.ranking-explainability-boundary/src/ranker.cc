#include "ranker.h"

#include <algorithm>
#include <utility>
#include <vector>

namespace nitr::case019 {

namespace {

int CategoryBonus(const Item& item) {
  if (item.category_match) {
    return 15;
  }

  return -8;
}

int FreshnessAdjustment(const Item& item) {
  if (item.freshness_days <= 3) {
    return 12;
  }

  if (item.freshness_days <= 14) {
    return 4;
  }

  return -10;
}

int PopularityAdjustment(const Item& item) {
  return item.popularity / 5;
}

}  // namespace

std::vector<RankedItem> Ranker::Rank(const std::vector<Item>& items) const {
  std::vector<RankedItem> ranked;
  ranked.reserve(items.size());

  for (const auto& item : items) {
    if (item.is_blocked) {
      continue;
    }

    ranked.push_back({item, ComputeScore(item)});
  }

  std::sort(ranked.begin(), ranked.end(),
            [](const RankedItem& left, const RankedItem& right) {
              if (left.final_score != right.final_score) {
                return left.final_score > right.final_score;
              }

              if (left.item.base_score != right.item.base_score) {
                return left.item.base_score > right.item.base_score;
              }

              return left.item.id < right.item.id;
            });

  return ranked;
}

int Ranker::ComputeScore(const Item& item) const {
  return item.base_score + CategoryBonus(item) + FreshnessAdjustment(item) +
         PopularityAdjustment(item);
}

}  // namespace nitr::case019
