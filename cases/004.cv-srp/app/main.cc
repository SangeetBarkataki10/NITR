#include <iostream>
#include <string>

#include "io_json.h"
#include "pipeline.h"
#include "types.h"

namespace {

struct Args {
  std::string input;
  std::string output;
};

bool ParseArgs(int argc, char** argv, Args* out) {
  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--input" && i + 1 < argc) {
      out->input = argv[++i];
    } else if (a == "--output" && i + 1 < argc) {
      out->output = argv[++i];
    }
  }
  if (out->input.empty() || out->output.empty()) {
    return false;
  }
  return true;
}

}  // namespace

int main(int argc, char** argv) {
  Args args;
  if (!ParseArgs(argc, argv, &args)) {
    std::cerr << "ERR_INVALID_SCHEMA\n";
    return nitr::case004::ToExitCode(nitr::case004::ErrorCode::kInvalidSchema);
  }

  // Parse
  nitr::case004::ParseOutput parsed =
      nitr::case004::ParsePairJsonFromFile(args.input);
  if (!parsed.input.has_value()) {
    std::cerr << nitr::case004::ToStderrString(parsed.err) << "\n";
    return nitr::case004::ToExitCode(parsed.err);
  }

  // Run SRP pipeline (must not call legacy)
  nitr::case004::RunOutput out = nitr::case004::RunPipeline(*parsed.input);

  if (out.code != nitr::case004::ErrorCode::kOk &&
      out.code != nitr::case004::ErrorCode::kRejected) {
    std::cerr << nitr::case004::ToStderrString(out.code) << "\n";
    return nitr::case004::ToExitCode(out.code);
  }

  // Always write result.json on accept/reject once estimation succeeded.
  if (!out.est.has_value() || !out.metrics.has_value() ||
      !out.decision.has_value()) {
    std::cerr << "ERR_ESTIMATION_FAILED\n";
    return nitr::case004::ToExitCode(
        nitr::case004::ErrorCode::kEstimationFailed);
  }

  nitr::case004::ErrorCode w = nitr::case004::WriteResultJsonToFile(
      args.output, *parsed.input, *out.est, *out.metrics, *out.decision);
  if (w != nitr::case004::ErrorCode::kOk) {
    std::cerr << nitr::case004::ToStderrString(w) << "\n";
    return nitr::case004::ToExitCode(w);
  }

  if (out.code == nitr::case004::ErrorCode::kRejected) {
    std::cerr << "ERR_REJECTED\n";
    return nitr::case004::ToExitCode(nitr::case004::ErrorCode::kRejected);
  }

  return 0;
}
