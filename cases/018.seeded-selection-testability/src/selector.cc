#include "selector.h"

#include <algorithm>
#include <random>
#include <stdexcept>
#include <utility>

#include "rules.h"
#include "sampler_v1.h"

namespace nitr::case018 {
namespace {

class RandomDeviceSampler final : public IndexSampler {
 public:
  RandomDeviceSampler() : engine_(std::random_device{}()) {}

  std::size_t NextIndex(std::size_t upper_exclusive) override {
    if (upper_exclusive == 0U) {
      throw std::invalid_argument("upper_exclusive must be > 0");
    }
    std::uniform_int_distribution<std::size_t> dist(0U, upper_exclusive - 1U);
    return dist(engine_);
  }

 private:
  std::mt19937 engine_;
};

}  // namespace

std::vector<std::string> SelectRecommendations(
    const std::vector<Candidate>& candidates, std::size_t k) {
  RandomDeviceSampler sampler;
  return SelectRecommendationsWithSampler(candidates, k, sampler);
}

std::vector<std::string> SelectRecommendationsWithSampler(
    const std::vector<Candidate>& candidates, std::size_t k,
    IndexSampler& sampler) {
  std::vector<Candidate> pool = BuildActivePool(candidates);
  SortByPolicyKey(&pool);
  if (pool.empty() || k == 0U) {
    return {};
  }

  // Starter pressure point: randomization is still globally applied to the full pool.
  for (std::size_t i = pool.size(); i > 1U; --i) {
    const std::size_t j = sampler.NextIndex(i);
    std::swap(pool[i - 1U], pool[j]);
  }

  const std::size_t take = std::min(k, pool.size());
  std::vector<std::string> ids;
  ids.reserve(take);
  for (std::size_t i = 0U; i < take; ++i) {
    ids.push_back(pool[i].id);
  }
  return ids;
}

std::vector<std::string> SelectRecommendationsReplay(
    const std::vector<Candidate>& candidates, std::size_t k,
    std::uint64_t seed) {
  std::vector<Candidate> pool = BuildActivePool(candidates);
  SortByPolicyKey(&pool);
  if (pool.empty() || k == 0U) {
    return {};
  }

  // Starter pressure point: replay path duplicates selection logic and does not use SamplerV1.
  std::mt19937 engine(static_cast<std::mt19937::result_type>(seed));
  std::shuffle(pool.begin(), pool.end(), engine);

  const std::size_t take = std::min(k, pool.size());
  std::vector<std::string> ids;
  ids.reserve(take);
  for (std::size_t i = 0U; i < take; ++i) {
    ids.push_back(pool[i].id);
  }
  return ids;
}

}  // namespace nitr::case018
