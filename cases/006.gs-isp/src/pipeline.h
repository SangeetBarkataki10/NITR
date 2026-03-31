#pragma once

#include <vector>

#include "types.h"

namespace nitr::case006 {

Image RenderTinyGs(const std::vector<Gaussian>& gaussians, const Camera& camera,
                   int width, int height);

float ImageChecksum(const Image& image);

}  // namespace nitr::case006
