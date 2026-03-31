#include "math_sampson.h"

// -------------------- Sampson error (squared) --------------------

namespace nitr::case004 {
double SampsonErrorSq(const Mat3& E, double x0, double y0, double x1,
                      double y1) {
  Vec3 X0{{x0, y0, 1.0}};
  Vec3 X1{{x1, y1, 1.0}};
  Vec3 Ex0 = Mul(E, X0);
  Vec3 Etx1 = Mul(Transpose(E), X1);
  double x1tEx0 = Dot(X1, Ex0);

  double denom =
      Ex0[0] * Ex0[0] + Ex0[1] * Ex0[1] + Etx1[0] * Etx1[0] + Etx1[1] * Etx1[1];
  if (denom <= 1e-18) {
    return std::numeric_limits<double>::infinity();
  }
  return (x1tEx0 * x1tEx0) / denom;
}

double MedianSampsonError(const NormalizedPair& norm, const Model& E_model,
                          const std::vector<bool>& inliers) {
  const size_t N = norm.x0.size();
  if (norm.x1.size() != N || inliers.size() != N) {
    return std::numeric_limits<double>::infinity();
  }

  Mat3 E;
  E[0][0] = E_model.mat3x3[0];
  E[0][1] = E_model.mat3x3[1];
  E[0][2] = E_model.mat3x3[2];
  E[1][0] = E_model.mat3x3[3];
  E[1][1] = E_model.mat3x3[4];
  E[1][2] = E_model.mat3x3[5];
  E[2][0] = E_model.mat3x3[6];
  E[2][1] = E_model.mat3x3[7];
  E[2][2] = E_model.mat3x3[8];

  std::vector<double> errs;
  errs.reserve(N);

  for (size_t i = 0; i < N; ++i) {
    if (!inliers[i]) {
      continue;
    }
    const double x0 = norm.x0[i][0];
    const double y0 = norm.x0[i][1];
    const double x1 = norm.x1[i][0];
    const double y1 = norm.x1[i][1];

    const double e2 = SampsonErrorSq(E, x0, y0, x1, y1);
    if (!std::isfinite(e2)) {
      continue;
    }
    // Return the Sampson error (not squared), since spec says "median_sampson_error".
    const double e = std::sqrt(std::max(0.0, e2));
    if (std::isfinite(e)) {
      errs.push_back(e);
    }
  }

  if (errs.empty()) {
    return std::numeric_limits<double>::infinity();
  }

  std::sort(errs.begin(), errs.end());
  return MedianOfSorted(&errs);
}

}  // namespace nitr::case004
