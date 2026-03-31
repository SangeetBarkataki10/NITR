#include "pipeline.h"

#include "composite.h"
#include "eval_shading.h"
#include "hit_buffer.h"
#include "project_and_bin.h"
#include "sort_hits.h"

namespace nitr::case006 {

Image RenderTinyGs(const std::vector<Gaussian>& gaussians, const Camera& camera,
                   int width, int height) {
  HitBuffer buffer;
  ProjectAndBin(gaussians, camera, &buffer);
  SortHitsByTileThenDepth(&buffer);
  EvalShading(gaussians, camera, &buffer);
  return CompositeToImage(buffer, width, height);
}

float ImageChecksum(const Image& image) {
  float sum = 0.0f;
  for (const Color& c : image.pixels) {
    sum += c.r + 2.0f * c.g + 3.0f * c.b;
  }
  return sum;
}

}  // namespace nitr::case006
