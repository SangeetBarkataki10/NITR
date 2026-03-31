#include "time_source.h"

#include <chrono>

namespace nitr::case009 {

std::int64_t SystemTimeSource::NowSeconds() const {
  return std::chrono::duration_cast<std::chrono::seconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

}  // namespace nitr::case009
