#include "library_catalog.h"

#include <algorithm>
#include <sstream>

namespace nitr::case013 {
namespace {

bool StartsWith(const std::string& text, const std::string& prefix) {
  if (prefix.size() > text.size()) {
    return false;
  }
  return text.compare(0, prefix.size(), prefix) == 0;
}

}  // namespace

std::vector<std::string> CatalogService::FindAvailableTitles(
    const std::vector<Book>& books, const std::string& prefix) const {
  std::vector<std::string> matches;
  for (const Book& book : books) {
    if (StartsWith(book.title, prefix)) {
      matches.push_back(book.title);
    }
  }

  std::sort(matches.begin(), matches.end());
  return matches;
}

std::string CatalogService::BuildCatalogDigest(
    const std::vector<Book>& books) const {
  std::ostringstream out;
  out << "Catalog Digest\n";
  for (const Book& book : books) {
    out << "- " << book.title << " by " << book.author << "\n";
  }
  return out.str();
}

}  // namespace nitr::case013
