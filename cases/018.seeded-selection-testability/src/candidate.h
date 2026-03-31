#ifndef CASE018_CANDIDATE_H_
#define CASE018_CANDIDATE_H_

#include <string>

namespace nitr::case018 {

struct Candidate {
  std::string id;
  int score = 0;
  bool eligible = false;
  bool is_fallback = false;
};

}  // namespace nitr::case018

#endif  // CASE018_CANDIDATE_H_
