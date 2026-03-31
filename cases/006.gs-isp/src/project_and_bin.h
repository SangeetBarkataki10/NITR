#pragma once

#include <vector>

#include "hit_buffer.h"
#include "types.h"

namespace nitr::case006 {

void ProjectAndBin(const std::vector<Gaussian>& gaussians, const Camera& camera,
                   HitBuffer* buffer);

}  // namespace nitr::case006
