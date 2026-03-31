#include <cassert>
#include <string>
#include <vector>

#include "applicant.h"
#include "audit_logger.h"
#include "loan_policy.h"
#include "loan_review_service.h"

namespace {

class MemoryAuditLogger final : public nitr::case010::AuditLogger {
 public:
  void Log(const std::string& message) override {
    messages.push_back(message);
  }

  std::vector<std::string> messages;
};

void TestEvaluateApplicantApprovesEligibleApplicant() {
  const nitr::case010::Applicant applicant{"alice", 750, 90000, 0.20};
  const nitr::case010::ReviewDecision decision =
      nitr::case010::EvaluateApplicant(applicant);

  assert(decision.approved);
  assert(decision.denial_reasons.empty());
}

void TestEvaluateApplicantReturnsOrderedReasons() {
  const nitr::case010::Applicant applicant{"carol", 680, 40000, 0.45};
  const nitr::case010::ReviewDecision decision =
      nitr::case010::EvaluateApplicant(applicant);

  assert(!decision.approved);
  assert(decision.denial_reasons.size() == 3);
  assert(decision.denial_reasons[0] == "low_credit");
  assert(decision.denial_reasons[1] == "low_income");
  assert(decision.denial_reasons[2] == "high_debt");
}

void TestReviewApplicantsCollectsApprovedIdsAndAuditMessages() {
  const std::vector<nitr::case010::Applicant> applicants = {
      {"alice", 750, 90000, 0.20},
      {"bob", 650, 80000, 0.30},
      {"carol", 710, 40000, 0.45},
  };

  MemoryAuditLogger logger;
  const nitr::case010::ReviewBatchResult result =
      nitr::case010::ReviewApplicants(applicants, &logger);

  assert(result.approved_ids.size() == 1);
  assert(result.approved_ids[0] == "alice");

  assert(logger.messages.size() == 3);
  assert(logger.messages[0] == "alice approved");
  assert(logger.messages[1] == "bob denied: low_credit");
  assert(logger.messages[2] == "carol denied: low_income,high_debt");
}

}  // namespace

int main() {
  TestEvaluateApplicantApprovesEligibleApplicant();
  TestEvaluateApplicantReturnsOrderedReasons();
  TestReviewApplicantsCollectsApprovedIdsAndAuditMessages();
  return 0;
}
