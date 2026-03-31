#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace nitr::case006 {

struct Vec3 {
  float x;
  float y;
  float z;
};

struct Color {
  float r;
  float g;
  float b;
};

struct Gaussian {
  Vec3 position;
  float opacity;
  std::array<float, 4> sh;
};

struct Camera {
  Vec3 origin;
  Vec3 view_dir;
};

struct Image {
  int width = 0;
  int height = 0;
  std::vector<Color> pixels;
};

}  // namespace nitr::case006
