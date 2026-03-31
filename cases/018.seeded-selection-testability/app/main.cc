#include <iostream>
#include <vector>

#include "candidate.h"
#include "selector.h"

int main() {
  using nitr::case018::Candidate;
  std::vector<Candidate> candidates = {
      {"alpha", 90, true, false},    {"beta", 90, true, false},
      {"gamma", 80, true, false},    {"fallback_a", 70, true, true},
      {"blocked", 99, false, false},
  };

  const std::vector<std::string> ids =
      nitr::case018::SelectRecommendations(candidates, 3);
  std::cout << "Selected:";
  for (const std::string& id : ids) {
    std::cout << ' ' << id;
  }
  std::cout << '\n';
  return 0;
}
