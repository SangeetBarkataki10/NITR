#include "sampler_v1.h"

#include <stdexcept>

namespace nitr::case018 {

namespace {
constexpr std::uint64_t kSeedXor = 0x9E3779B97F4A7C15ULL;
constexpr std::uint64_t kMultiplier = 6364136223846793005ULL;
constexpr std::uint64_t kIncrement = 1442695040888963407ULL;
}  // namespace

SamplerV1::SamplerV1(std::uint64_t seed) : state_(seed ^ kSeedXor) {}

std::size_t SamplerV1::NextIndex(std::size_t upper_exclusive) {
  if (upper_exclusive == 0U) {
    throw std::invalid_argument("upper_exclusive must be > 0");
  }
  state_ = state_ * kMultiplier + kIncrement;
  return static_cast<std::size_t>((state_ >> 32U) % upper_exclusive);
}

}  // namespace nitr::case018
