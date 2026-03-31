#ifndef CASE018_SELECTOR_H_
#define CASE018_SELECTOR_H_

#include <cstddef>
#include <cstdint>
#include <vector>

#include "candidate.h"

namespace nitr::case018 {

class IndexSampler {
 public:
  virtual ~IndexSampler() = default;
  virtual std::size_t NextIndex(std::size_t upper_exclusive) = 0;
};

// Default production path. Uses non-fixed randomness.
std::vector<std::string> SelectRecommendations(
    const std::vector<Candidate>& candidates, std::size_t k);

// Deterministic replay path. Must follow SamplerV1 contract.
std::vector<std::string> SelectRecommendationsReplay(
    const std::vector<Candidate>& candidates, std::size_t k,
    std::uint64_t seed);

// Policy function with explicit sampler seam for deterministic testing.
std::vector<std::string> SelectRecommendationsWithSampler(
    const std::vector<Candidate>& candidates, std::size_t k,
    IndexSampler& sampler);

}  // namespace nitr::case018

#endif  // CASE018_SELECTOR_H_
