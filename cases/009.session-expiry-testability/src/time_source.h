#pragma once

#include <cstdint>

namespace nitr::case009 {

class TimeSource {
 public:
  virtual ~TimeSource() = default;
  virtual std::int64_t NowSeconds() const = 0;
};

class SystemTimeSource final : public TimeSource {
 public:
  std::int64_t NowSeconds() const override;
};

}  // namespace nitr::case009
