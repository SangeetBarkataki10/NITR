#pragma once

#include "hit_buffer.h"
#include "types.h"

namespace nitr::case006 {

Image CompositeToImage(const HitBuffer& buffer, int width, int height);

}  // namespace nitr::case006
