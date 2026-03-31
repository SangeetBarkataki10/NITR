#pragma once

#include <stdexcept>
#include <string>

namespace nitr::case016 {

enum class DeviceKind {
  kCpu,
  kGpu,
};

inline std::string ToString(const DeviceKind device) {
  if (device == DeviceKind::kCpu) {
    return "cpu";
  }
  return "gpu";
}

inline DeviceKind DeviceKindFromString(const std::string& value) {
  if (value == "cpu") {
    return DeviceKind::kCpu;
  }
  if (value == "gpu") {
    return DeviceKind::kGpu;
  }
  throw std::runtime_error("Unknown device kind: " + value);
}

}  // namespace nitr::case016
