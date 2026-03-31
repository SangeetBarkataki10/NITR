#ifndef CASE018_RULES_H_
#define CASE018_RULES_H_

#include <vector>

#include "candidate.h"

namespace nitr::case018 {

std::vector<Candidate> BuildActivePool(
    const std::vector<Candidate>& candidates);

void SortByPolicyKey(std::vector<Candidate>* pool);

}  // namespace nitr::case018

#endif  // CASE018_RULES_H_
