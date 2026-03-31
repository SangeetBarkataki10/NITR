#include "pricing.h"

namespace nitr::case005 {

RuleRegistry& RuleRegistry::Instance() {
  static RuleRegistry inst;
  return inst;
}

void RuleRegistry::Register(const std::string& key, RuleFactory factory) {
  factories_[key] = std::move(factory);
}

std::unique_ptr<IRule> RuleRegistry::Create(const std::string& key,
                                            const RuleContext& ctx) const {
  auto it = factories_.find(key);
  if (it == factories_.end()) {
    return nullptr;
  }
  return (it->second)(ctx);
}

PriceResult ComputeFinalPrice(const Order& order, int milestone) {
  PriceResult out;
  int64_t price = order.subtotal_cents;

  RuleContext ctx{order, milestone};

  for (const auto& code : order.coupons) {
    auto rule = RuleRegistry::Instance().Create(code, ctx);
    if (!rule) {
      continue;  // spec decides: ignore unknown vs error
    }
    if (!rule->Applicable(ctx)) {
      continue;
    }
    price += rule->DeltaCents(ctx, price);
    out.applied_rules.push_back(rule->Id());
  }

  out.final_price_cents = price;
  return out;
}

}  // namespace nitr::case005
