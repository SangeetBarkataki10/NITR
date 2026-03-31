#include "sort_hits.h"

#include <algorithm>

namespace nitr::case006 {

void SortHitsByTileThenDepth(HitBuffer* buffer) {
  std::vector<Hit>& hits = buffer->MutableHits();
  std::stable_sort(hits.begin(), hits.end(), [](const Hit& a, const Hit& b) {
    if (a.tile_id != b.tile_id) {
      return a.tile_id < b.tile_id;
    }
    return a.depth < b.depth;
  });
}

}  // namespace nitr::case006
