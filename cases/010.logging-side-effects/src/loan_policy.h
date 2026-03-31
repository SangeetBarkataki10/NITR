#ifndef NITR_LOAN_POLICY_H_
#define NITR_LOAN_POLICY_H_

#include <string>
#include <vector>

#include "applicant.h"

namespace nitr::case010 {

struct ReviewDecision {
  bool approved = false;
  std::vector<std::string> denial_reasons;
};

ReviewDecision EvaluateApplicant(const Applicant& applicant);

}  // namespace nitr::case010

#endif  // NITR_LOAN_POLICY_H_
