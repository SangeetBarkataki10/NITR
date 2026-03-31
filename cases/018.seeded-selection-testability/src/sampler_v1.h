#ifndef CASE018_SAMPLER_V1_H_
#define CASE018_SAMPLER_V1_H_

#include <cstddef>
#include <cstdint>

#include "selector.h"

namespace nitr::case018 {

// SamplerV1 fixed contract:
//   state = seed ^ 0x9E3779B97F4A7C15ULL
//   state = state * 6364136223846793005ULL + 1442695040888963407ULL
//   NextIndex(n) = ((state >> 32) % n), n > 0
class SamplerV1 final : public IndexSampler {
 public:
  explicit SamplerV1(std::uint64_t seed);

  std::size_t NextIndex(std::size_t upper_exclusive) override;

 private:
  std::uint64_t state_;
};

}  // namespace nitr::case018

#endif  // CASE018_SAMPLER_V1_H_
