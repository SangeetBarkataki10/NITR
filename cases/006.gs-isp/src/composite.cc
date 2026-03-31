#include "composite.h"

#include <vector>

namespace nitr::case006 {

Image CompositeToImage(const HitBuffer& buffer, int width, int height) {
  Image image;
  image.width = width;
  image.height = height;
  image.pixels.assign(static_cast<std::size_t>(width * height),
                      Color{0.0f, 0.0f, 0.0f});

  std::vector<float> transmittance(static_cast<std::size_t>(width * height),
                                   1.0f);

  for (const Hit& hit : buffer.Hits()) {
    const int x = hit.tile_id;
    const int y = 0;
    const int idx = y * width + x;
    const float weight =
        transmittance[static_cast<std::size_t>(idx)] * hit.opacity;
    image.pixels[static_cast<std::size_t>(idx)].r += weight * hit.color.r;
    image.pixels[static_cast<std::size_t>(idx)].g += weight * hit.color.g;
    image.pixels[static_cast<std::size_t>(idx)].b += weight * hit.color.b;
    transmittance[static_cast<std::size_t>(idx)] *= (1.0f - hit.opacity);
  }

  return image;
}

}  // namespace nitr::case006
