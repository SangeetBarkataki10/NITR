#ifndef NITR_LOAN_REVIEW_SERVICE_H_
#define NITR_LOAN_REVIEW_SERVICE_H_

#include <string>
#include <vector>

#include "applicant.h"
#include "audit_logger.h"

namespace nitr::case010 {

struct ReviewBatchResult {
  std::vector<std::string> approved_ids;
};

ReviewBatchResult ReviewApplicants(const std::vector<Applicant>& applicants,
                                   AuditLogger* logger);

}  // namespace nitr::case010

#endif  // NITR_LOAN_REVIEW_SERVICE_H_
