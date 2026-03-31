#pragma once

#include <string>
#include <vector>

namespace nitr::case013 {

struct Book {
  std::string id;
  std::string title;
  std::string author;
  bool archived = false;
};

class CatalogService {
 public:
  std::vector<std::string> FindAvailableTitles(const std::vector<Book>& books,
                                               const std::string& prefix) const;

  std::string BuildCatalogDigest(const std::vector<Book>& books) const;
};

}  // namespace nitr::case013
