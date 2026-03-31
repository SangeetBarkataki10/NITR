#include <iostream>
#include <vector>

#include "library_catalog.h"

int main() {
  nitr::case013::CatalogService service;
  const std::vector<nitr::case013::Book> books = {
      {"b1", "Atlas", "Ada", false},
      {"b2", "Archive of Fog", "Bea", true},
      {"b3", "Atomic Habits", "James Clear", false},
  };

  const auto matches = service.FindAvailableTitles(books, "At");
  std::cout << "Matches:\n";
  for (const auto& title : matches) {
    std::cout << "  " << title << "\n";
  }

  std::cout << "\n" << service.BuildCatalogDigest(books);
  return 0;
}
