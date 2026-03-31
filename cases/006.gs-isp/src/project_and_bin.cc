#include "project_and_bin.h"

#include <cmath>

namespace nitr::case006 {

void ProjectAndBin(const std::vector<Gaussian>& gaussians, const Camera& camera,
                   HitBuffer* buffer) {
  for (std::size_t i = 0; i < gaussians.size(); ++i) {
    const Gaussian& g = gaussians[i];
    Hit hit;
    hit.gaussian_id = static_cast<int>(i);
    hit.depth = g.position.z - camera.origin.z;
    hit.tile_id = g.position.x < 0.5f ? 0 : 1;
    hit.opacity = g.opacity;
    hit.world_position = g.position;
    hit.sh_band = 1;
    buffer->AddHit(hit);
  }
}

}  // namespace nitr::case006
