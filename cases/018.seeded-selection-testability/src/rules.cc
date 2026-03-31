#include "rules.h"

#include <algorithm>
#include <utility>

namespace nitr::case018 {

std::vector<Candidate> BuildActivePool(
    const std::vector<Candidate>& candidates) {
  std::vector<Candidate> primary;
  std::vector<Candidate> fallback;

  for (const Candidate& c : candidates) {
    if (!c.eligible) {
      continue;
    }
    if (c.is_fallback) {
      fallback.push_back(c);
    } else {
      primary.push_back(c);
    }
  }

  return !primary.empty() ? std::move(primary) : std::move(fallback);
}

void SortByPolicyKey(std::vector<Candidate>* pool) {
  std::sort(pool->begin(), pool->end(),
            [](const Candidate& a, const Candidate& b) {
              if (a.score != b.score) {
                return a.score > b.score;
              }
              return a.id < b.id;
            });
}

}  // namespace nitr::case018
