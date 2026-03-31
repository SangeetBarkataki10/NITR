#include "eval_shading.h"

#include <algorithm>

namespace nitr::case006 {

void EvalShading(const std::vector<Gaussian>& gaussians, const Camera& camera,
                 HitBuffer* buffer) {
  for (Hit& hit : buffer->MutableHits()) {
    const Gaussian& g = gaussians[hit.gaussian_id];
    const float view_factor = std::max(0.0f, camera.view_dir.z);
    hit.color.r = g.sh[0] + g.sh[1] * view_factor;
    hit.color.g = g.sh[0] + g.sh[2] * view_factor;
    hit.color.b = g.sh[0] + g.sh[3] * view_factor;
  }
}

}  // namespace nitr::case006
