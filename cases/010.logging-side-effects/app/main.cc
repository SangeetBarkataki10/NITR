#include <iostream>
#include <vector>

#include "applicant.h"
#include "audit_logger.h"
#include "loan_review_service.h"

int main() {
  std::vector<nitr::case010::Applicant> applicants = {
      {"alice", 750, 90000, 0.20},
      {"bob", 650, 80000, 0.30},
  };

  nitr::case010::NullAuditLogger logger;
  const nitr::case010::ReviewBatchResult result =
      nitr::case010::ReviewApplicants(applicants, &logger);

  std::cout << "approved=" << result.approved_ids.size() << std::endl;
  return 0;
}
