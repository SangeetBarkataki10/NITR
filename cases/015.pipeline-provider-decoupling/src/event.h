#pragma once

#include <string>

namespace nitr::case015 {

struct Event {
  std::string source_id;
  std::string payload;
  int score = 0;
};

}  // namespace nitr::case015
