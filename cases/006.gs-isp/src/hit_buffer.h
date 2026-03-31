#pragma once

#include <vector>

#include "types.h"

namespace nitr::case006 {

struct Hit {
  int tile_id = 0;
  int gaussian_id = 0;
  float depth = 0.0f;
  float opacity = 0.0f;
  Color color{0.0f, 0.0f, 0.0f};

  // The following fields are intentionally not needed by every stage.
  // They are exposed anyway in the legacy design.
  Vec3 normal{0.0f, 0.0f, 1.0f};
  Vec3 world_position{0.0f, 0.0f, 0.0f};
  int sh_band = 0;
  bool touched_by_debugger = false;
};

class HitBuffer {
 public:
  void AddHit(const Hit& hit) {
    hits_.push_back(hit);
  }

  std::vector<Hit>& MutableHits() {
    return hits_;
  }
  const std::vector<Hit>& Hits() const {
    return hits_;
  }

  std::size_t Size() const {
    return hits_.size();
  }

 private:
  std::vector<Hit> hits_;
};

}  // namespace nitr::case006
