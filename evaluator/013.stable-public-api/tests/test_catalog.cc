#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "library_catalog.h"

namespace {

bool Expect(bool condition, const std::string& message) {
  if (!condition) {
    std::cerr << "FAIL: " << message << "\n";
    return false;
  }
  return true;
}

bool ExpectEqual(const std::vector<std::string>& actual,
                 const std::vector<std::string>& expected,
                 const std::string& message) {
  if (actual != expected) {
    std::cerr << "FAIL: " << message << "\n";
    std::cerr << "Expected:";
    for (const auto& x : expected) {
      std::cerr << " [" << x << "]";
    }
    std::cerr << "\nActual:";
    for (const auto& x : actual) {
      std::cerr << " [" << x << "]";
    }
    std::cerr << "\n";
    return false;
  }
  return true;
}

}  // namespace

int main() {
  nitr::case013::CatalogService service;
  const std::vector<nitr::case013::Book> books = {
      {"b1", "Atlas", "Ada", false},
      {"b2", "Archive of Fog", "Bea", true},
      {"b3", "Atomic Habits", "James Clear", false},
      {"b4", "A Tale of Two Cities", "Charles Dickens", false},
  };

  bool ok = true;

  ok &= ExpectEqual(service.FindAvailableTitles(books, "At"),
                    {"Atlas", "Atomic Habits"},
                    "archived titles must be excluded from prefix lookup");

  const std::string digest = service.BuildCatalogDigest(books);
  ok &= Expect(digest.find("Archive of Fog") == std::string::npos,
               "catalog digest must exclude archived books");
  ok &= Expect(digest.find("Atlas by Ada") != std::string::npos,
               "visible books must remain in the digest");
  ok &= Expect(digest.find("Atomic Habits by James Clear") != std::string::npos,
               "non-archived matching content must remain visible");

  if (!ok) {
    return EXIT_FAILURE;
  }

  std::cout << "All catalog tests passed.\n";
  return EXIT_SUCCESS;
}
