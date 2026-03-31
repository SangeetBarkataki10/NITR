#include "providers_builtin.h"

#include <cctype>

namespace nitr::case008 {

std::string GeometryProvider::BuildLayer(const std::string& payload) const {
  // Toy "geometry": count alnum chars.
  int count = 0;
  for (char c : payload) {
    if (std::isalnum(static_cast<unsigned char>(c)) != 0) {
      count++;
    }
  }
  return std::string("alnum_count=") + std::to_string(count);
}

std::string SemanticsProvider::BuildLayer(const std::string& payload) const {
  // Toy "semantics": echo first word (up to 16 chars, stop at whitespace).
  std::string w;
  for (char c : payload) {
    if (std::isspace(static_cast<unsigned char>(c)) != 0) {
      if (!w.empty()) {
        break;
      }
      continue;
    }
    w.push_back(c);
    if (w.size() >= 16) {
      break;
    }
  }
  if (w.empty()) {
    w = "EMPTY";
  }
  return std::string("first_token=") + w;
}

}  // namespace nitr::case008
