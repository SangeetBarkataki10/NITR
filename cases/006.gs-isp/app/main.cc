#include <iostream>
#include <vector>

#include "pipeline.h"
#include "types.h"

int main() {
  std::vector<nitr::case006::Gaussian> gaussians = {
      {{0.25f, 0.0f, 2.0f}, 0.5f, {0.2f, 0.1f, 0.0f, 0.0f}},
      {{0.75f, 0.0f, 1.0f}, 0.6f, {0.1f, 0.0f, 0.2f, 0.0f}},
      {{0.25f, 0.0f, 3.0f}, 0.4f, {0.3f, 0.0f, 0.0f, 0.1f}},
  };
  nitr::case006::Camera camera{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
  const nitr::case006::Image image =
      nitr::case006::RenderTinyGs(gaussians, camera, 2, 1);
  std::cout << nitr::case006::ImageChecksum(image) << std::endl;
  return 0;
}
