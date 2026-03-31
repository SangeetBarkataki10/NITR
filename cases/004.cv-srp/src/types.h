#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace nitr::case004 {

enum ErrorCode {
  kOk = 0,
  kInvalidJson = 1,
  kInvalidSchema = 2,
  kEstimationFailed = 3,
  kRejected = 4,
};

inline const char* ToStderrString(ErrorCode c) {
  switch (c) {
    case ErrorCode::kInvalidJson:
      return "ERR_INVALID_JSON";
    case ErrorCode::kInvalidSchema:
      return "ERR_INVALID_SCHEMA";
    case ErrorCode::kEstimationFailed:
      return "ERR_ESTIMATION_FAILED";
    case ErrorCode::kRejected:
      return "ERR_REJECTED";
    default:
      return "";
  }
}

inline int ToExitCode(ErrorCode c) {
  switch (c) {
    case ErrorCode::kOk:
      return 0;
    case ErrorCode::kInvalidJson:
    case ErrorCode::kInvalidSchema:
      return 2;
    case ErrorCode::kEstimationFailed:
      return 3;
    case ErrorCode::kRejected:
      return 4;
    default:
      return 1;
  }
}

struct Camera {
  double fx = 0.0;
  double fy = 0.0;
  double cx = 0.0;
  double cy = 0.0;
};

struct Frame {
  std::vector<std::array<double, 2>> keypoints_px;  // (x,y)
};

struct Match {
  int i0 = -1;
  int i1 = -1;
};

struct Options {
  std::string model = "E";
  double ransac_thresh_px = 1.0;
  int max_iters = 2000;
  uint32_t seed = 0xC0FFEEu;
};

struct PairInput {
  Camera cam;
  Frame f0;
  Frame f1;
  std::vector<Match> matches;
  Options opt;
};

struct NormalizedPair {
  // normalized coordinates for matched points, aligned with matches order
  std::vector<std::array<double, 2>> x0;
  std::vector<std::array<double, 2>> x1;
};

struct Model {
  std::string type = "E";
  std::array<double, 9> mat3x3{};  // row-major
};

struct EstimationOutput {
  Model model;
  std::vector<bool> inliers;  // size == matches
};

struct Metrics {
  int num_matches = 0;
  int num_inliers = 0;
  double inlier_ratio = 0.0;
  double median_sampson_error = 0.0;
};

enum class Decision { kAccept, kReject };

struct Result {
  std::optional<EstimationOutput> est;
  std::optional<Metrics> metrics;
  std::optional<Decision> decision;
};

}  // namespace nitr::case004
