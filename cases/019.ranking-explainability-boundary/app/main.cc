#include <iostream>
#include <vector>

#include "item.h"
#include "ranker.h"

int main() {
  const std::vector<nitr::case019::Item> items = {
      {101, "Maple Bench", 70, true, 6, 48, false},
      {102, "Oak Bench", 74, false, 21, 61, false},
      {103, "Compact Stool", 66, true, 2, 35, false},
      {104, "Archive Sample", 88, true, 1, 90, true},
  };

  nitr::case019::Ranker ranker;
  const auto results = ranker.Rank(items);

  std::cout << "Ranked items\n";
  for (const auto& entry : results) {
    std::cout << entry.item.id << " | " << entry.item.name
              << " | score=" << entry.final_score << "\n";
  }

  return 0;
}
