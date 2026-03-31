#ifndef NITR_APPLICANT_H_
#define NITR_APPLICANT_H_

#include <string>

namespace nitr::case010 {

struct Applicant {
  std::string id;
  int credit_score = 0;
  int annual_income = 0;
  double debt_ratio = 0.0;
};

}  // namespace nitr::case010

#endif  // NITR_APPLICANT_H_
