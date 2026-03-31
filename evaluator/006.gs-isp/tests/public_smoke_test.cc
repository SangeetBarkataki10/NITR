#include <cassert>
#include <cmath>
#include <vector>

#include "pipeline.h"
#include "types.h"

namespace {

bool NearlyEqual(float a, float b, float eps = 1e-5f) {
  return std::fabs(a - b) < eps;
}

}  // namespace

int main() {
  std::vector<nitr::case006::Gaussian> gaussians = {
      {{0.25f, 0.0f, 2.0f}, 0.5f, {0.2f, 0.1f, 0.0f, 0.0f}},
      {{0.75f, 0.0f, 1.0f}, 0.6f, {0.1f, 0.0f, 0.2f, 0.0f}},
      {{0.25f, 0.0f, 3.0f}, 0.4f, {0.3f, 0.0f, 0.0f, 0.1f}},
  };

  nitr::case006::Camera camera{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
  const nitr::case006::Image image =
      nitr::case006::RenderTinyGs(gaussians, camera, 2, 1);

  assert(image.width == 2);
  assert(image.height == 1);
  assert(image.pixels.size() == 2);
  assert(NearlyEqual(nitr::case006::ImageChecksum(image), 1.67f));
  return 0;
}
