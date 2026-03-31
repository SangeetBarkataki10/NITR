#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace nitr::case005 {

inline constexpr int kPricingApiVersion = 1;

struct Order {
  int64_t subtotal_cents = 0;
  bool is_member = false;
  int items = 0;
  std::vector<std::string> coupons;
};

struct PriceResult {
  int64_t final_price_cents = 0;
  std::vector<std::string> applied_rules;
};

// ---- OCP extension point ----
struct RuleContext {
  const Order& order;
  int milestone = 1;
};

/**
 * API frozen (v1). Do not change without bumping kPricingApiVersion.
 *
 * Contract:
 *  - Id(): stable identifier used for diagnostics / applied_rules.
 *  - Applicable(): must be deterministic for the same context.
 *  - DeltaCents(): returns price delta in cents (negative = discount).
 *  - Implementations should not throw exceptions.
 */
class IRule {
 public:
  virtual ~IRule() = default;
  virtual std::string Id() const = 0;
  virtual bool Applicable(const RuleContext& ctx) const = 0;
  virtual int64_t DeltaCents(const RuleContext& ctx,
                             int64_t current_price_cents) const = 0;
};

using RuleFactory = std::function<std::unique_ptr<IRule>(const RuleContext&)>;

/**
 * API frozen (v1). Do not change without bumping kPricingApiVersion.
 *
 * Contract:
 *  - Register(key, factory) overwrites existing factory for the same key.
 *  - Create(key, ctx) returns nullptr if key not found.
 *  - Does not throw exceptions.
 */
class RuleRegistry {
 public:
  static RuleRegistry& Instance();

  RuleRegistry(const RuleRegistry&) = delete;
  RuleRegistry& operator=(const RuleRegistry&) = delete;
  RuleRegistry(RuleRegistry&&) = delete;
  RuleRegistry& operator=(RuleRegistry&&) = delete;

  void Register(const std::string& key, RuleFactory factory);

  // Returns nullptr if not found.
  std::unique_ptr<IRule> Create(const std::string& key,
                                const RuleContext& ctx) const;

 private:
  RuleRegistry() = default;
  std::unordered_map<std::string, RuleFactory> factories_;
};

/**
 * Core pricing entrypoint (protected core candidate).
 * API frozen (v1). Do not change without bumping kPricingApiVersion.
 *
 * OCP/Gate2b expectation:
 *  - Coupon-driven behavior must be obtained via RuleRegistry::Create(...),
 *    rather than branching on coupon code/type inside the core.
 */
PriceResult ComputeFinalPrice(const Order& order, int milestone);

}  // namespace nitr::case005
