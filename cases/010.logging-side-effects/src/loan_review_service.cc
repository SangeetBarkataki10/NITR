#include "loan_review_service.h"

#include <cstddef>

#include "loan_policy.h"

namespace nitr::case010 {

ReviewBatchResult ReviewApplicants(const std::vector<Applicant>& applicants,
                                   AuditLogger* logger) {
  ReviewBatchResult result;
  for (std::size_t i = 0; i < applicants.size(); ++i) {
    const ReviewDecision decision = EvaluateApplicant(applicants[i]);
    if (logger != nullptr) {
      logger->Log("pending");
    }
    if (decision.approved) {
      result.approved_ids.push_back(applicants[i].id);
    }
  }
  return result;
}

}  // namespace nitr::case010
