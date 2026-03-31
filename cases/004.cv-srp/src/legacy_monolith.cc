#include "legacy_monolith.h"

#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "math_sampson.h"
#include "types.h"

namespace nitr::case004 {
namespace {

bool ReadAll(const std::string& path, std::string* out) {
  std::ifstream ifs(path);
  if (!ifs) {
    return false;
  }
  out->assign((std::istreambuf_iterator<char>(ifs)),
              std::istreambuf_iterator<char>());
  return true;
}

bool WriteAll(const std::string& path, const std::string& s) {
  std::ofstream ofs(path);
  if (!ofs) {
    return false;
  }
  ofs << s;
  return true;
}

// ---------- Parsing + schema validation (monolithic, legacy-style) ----------
struct Parsed {
  PairInput in;
};

std::optional<Parsed> ParseAndValidate(const nlohmann::json& j,
                                       ErrorCode* err) {
  // Required top-level fields
  if (!j.is_object() || !j.contains("camera") || !j.contains("frame0") ||
      !j.contains("frame1") || !j.contains("matches") ||
      !j.contains("options")) {
    *err = ErrorCode::kInvalidSchema;
    return std::nullopt;
  }

  Parsed p;
  try {
    const auto& c = j.at("camera");
    p.in.cam.fx = c.at("fx").get<double>();
    p.in.cam.fy = c.at("fy").get<double>();
    p.in.cam.cx = c.at("cx").get<double>();
    p.in.cam.cy = c.at("cy").get<double>();

    const auto& f0 = j.at("frame0").at("keypoints");
    const auto& f1 = j.at("frame1").at("keypoints");
    if (!f0.is_array() || !f1.is_array()) {
      *err = ErrorCode::kInvalidSchema;
      return std::nullopt;
    }
    for (const auto& kp : f0) {
      p.in.f0.keypoints_px.push_back(
          {kp.at(0).get<double>(), kp.at(1).get<double>()});
    }
    for (const auto& kp : f1) {
      p.in.f1.keypoints_px.push_back(
          {kp.at(0).get<double>(), kp.at(1).get<double>()});
    }

    const auto& ms = j.at("matches");
    if (!ms.is_array()) {
      *err = ErrorCode::kInvalidSchema;
      return std::nullopt;
    }
    for (const auto& m : ms) {
      p.in.matches.push_back({m.at(0).get<int>(), m.at(1).get<int>()});
    }

    const auto& opt = j.at("options");
    p.in.opt.model = opt.at("model").get<std::string>();
    p.in.opt.ransac_thresh_px = opt.at("ransac_thresh_px").get<double>();
    p.in.opt.max_iters = opt.at("max_iters").get<int>();
    if (opt.contains("seed")) {
      p.in.opt.seed = opt.at("seed").get<uint32_t>();
    }
  } catch (...) {
    *err = ErrorCode::kInvalidSchema;
    return std::nullopt;
  }

  // Constraints
  if (p.in.cam.fx <= 0.0 || p.in.cam.fy <= 0.0) {
    *err = ErrorCode::kInvalidSchema;
    return std::nullopt;
  }
  if (p.in.f0.keypoints_px.empty() || p.in.f1.keypoints_px.empty()) {
    *err = ErrorCode::kInvalidSchema;
    return std::nullopt;
  }
  if (p.in.opt.ransac_thresh_px <= 0.0 || p.in.opt.max_iters < 1 ||
      p.in.opt.max_iters > 10000000) {
    *err = ErrorCode::kInvalidSchema;
    return std::nullopt;
  }
  if (p.in.opt.model != "E") {
    *err = ErrorCode::kInvalidSchema;
    return std::nullopt;
  }

  for (const auto& m : p.in.matches) {
    if (m.i0 < 0 || m.i0 >= static_cast<int>(p.in.f0.keypoints_px.size()) ||
        m.i1 < 0 || m.i1 >= static_cast<int>(p.in.f1.keypoints_px.size())) {
      *err = ErrorCode::kInvalidSchema;
      return std::nullopt;
    }
  }

  *err = ErrorCode::kOk;
  return p;
}

// ---------- Normalize ----------
NormalizedPair Normalize(const PairInput& in) {
  NormalizedPair norm;
  norm.x0.reserve(in.matches.size());
  norm.x1.reserve(in.matches.size());
  for (const auto& m : in.matches) {
    const auto& p0 = in.f0.keypoints_px[m.i0];
    const auto& p1 = in.f1.keypoints_px[m.i1];
    const double x0 = (p0[0] - in.cam.cx) / in.cam.fx;
    const double y0 = (p0[1] - in.cam.cy) / in.cam.fy;
    const double x1 = (p1[0] - in.cam.cx) / in.cam.fx;
    const double y1 = (p1[1] - in.cam.cy) / in.cam.fy;
    norm.x0.push_back({x0, y0});
    norm.x1.push_back({x1, y1});
  }
  return norm;
}

// ---------- Policy thresholds (must match SRP policy) ----------
Decision Decide(const Metrics& m) {
  if (m.num_inliers >= 30 && m.inlier_ratio >= 0.25 &&
      m.median_sampson_error <= 1.0) {
    return Decision::kAccept;
  }
  return Decision::kReject;
}

// ---------- Serialize ----------
nlohmann::json ToJson(const EstimationOutput& est, const Metrics& m,
                      Decision d) {
  nlohmann::json j;
  j["model"] = est.model.type;

  nlohmann::json mat = nlohmann::json::array();
  for (int r = 0; r < 3; ++r) {
    nlohmann::json row = nlohmann::json::array();
    for (int c = 0; c < 3; ++c) {
      row.push_back(est.model.mat3x3[r * 3 + c]);
    }
    mat.push_back(row);
  }
  j["params"] = {{"E", mat}};

  nlohmann::json inl = nlohmann::json::array();
  for (bool b : est.inliers) {
    inl.push_back(b);
  }
  j["inliers"] = inl;

  j["metrics"] = {
      {"num_matches", m.num_matches},
      {"num_inliers", m.num_inliers},
      {"inlier_ratio", m.inlier_ratio},
      {"median_sampson_error", m.median_sampson_error},
  };

  j["decision"] = (d == Decision::kAccept) ? "ACCEPT" : "REJECT";
  return j;
}

// -------------------- 8-point from subset (via eig of A^T A) --------------------
static inline std::optional<Mat3> EightPointE(const NormalizedPair& norm,
                                              const std::array<int, 8>& idx8) {
  // Build ATA (9x9)
  double ATA[9][9];
  for (int r = 0; r < 9; ++r) {
    for (int c = 0; c < 9; ++c) {
      ATA[r][c] = 0.0;
    }
  }

  for (int k = 0; k < 8; ++k) {
    int i = idx8[k];
    const double x0 = norm.x0[i][0];
    const double y0 = norm.x0[i][1];
    const double x1 = norm.x1[i][0];
    const double y1 = norm.x1[i][1];

    // row a (1x9)
    double a[9] = {x1 * x0, x1 * y0, x1, y1 * x0, y1 * y0, y1, x0, y0, 1.0};
    // ATA += a^T a
    for (int r = 0; r < 9; ++r) {
      for (int c = r; c < 9; ++c) {
        ATA[r][c] += a[r] * a[c];
      }
    }
  }
  // mirror
  for (int r = 0; r < 9; ++r) {
    for (int c = 0; c < r; ++c) {
      ATA[r][c] = ATA[c][r];
    }
  }

  // eig(ATA): take smallest eigenvector
  double Awork[9][9];
  for (int r = 0; r < 9; ++r) {
    for (int c = 0; c < 9; ++c) {
      Awork[r][c] = ATA[r][c];
    }
  }
  auto eig = JacobiEigenSymmetric<9>(Awork);

  int min_i = 0;
  double min_v = eig.d[0];
  for (int i = 1; i < 9; ++i) {
    if (eig.d[i] < min_v) {
      min_v = eig.d[i];
      min_i = i;
    }
  }

  // eigenvector is column min_i
  double evec[9];
  for (int r = 0; r < 9; ++r) {
    evec[r] = eig.v[r][min_i];
  }

  Mat3 E;
  E[0][0] = evec[0];
  E[0][1] = evec[1];
  E[0][2] = evec[2];
  E[1][0] = evec[3];
  E[1][1] = evec[4];
  E[1][2] = evec[5];
  E[2][0] = evec[6];
  E[2][1] = evec[7];
  E[2][2] = evec[8];

  // enforce rank-2 essential constraint
  Mat3 E2 = EnforceRank2Essential(E);
  return E2;
}

std::optional<EstimationOutput> EstimateEssentialRansac(
    const PairInput& in, const NormalizedPair& norm) {
  const int N = static_cast<int>(norm.x0.size());
  if (N < 8) {
    return std::nullopt;
  }

  // Convert pixel threshold to normalized threshold (approx).
  const double f = 0.5 * (in.cam.fx + in.cam.fy);
  if (f <= 0.0) {
    return std::nullopt;
  }
  const double th = in.opt.ransac_thresh_px / f;
  const double th2 = th * th;

  std::mt19937 rng(static_cast<uint32_t>(in.opt.seed));
  std::uniform_int_distribution<int> uni(0, N - 1);

  int best_inliers = -1;
  double best_cost = std::numeric_limits<double>::infinity();
  Mat3 bestE;
  std::vector<bool> best_mask;

  auto sample8 = [&](std::array<int, 8>* idx8) -> bool {
    // sample 8 unique indices deterministically
    std::array<int, 8> s{};
    int tries = 0;
    for (int k = 0; k < 8;) {
      if (++tries > 10000) {
        return false;
      }
      int r = uni(rng);
      bool dup = false;
      for (int j = 0; j < k; ++j) {
        if (s[j] == r) {
          dup = true;
          break;
        }
      }
      if (!dup) {
        s[k++] = r;
      }
    }
    *idx8 = s;
    return true;
  };

  const int iters = std::min(in.opt.max_iters, 10000000);
  for (int it = 0; it < iters; ++it) {
    std::array<int, 8> idx8;
    if (!sample8(&idx8)) {
      break;
    }

    auto Eopt = EightPointE(norm, idx8);
    if (!Eopt.has_value()) {
      continue;
    }
    const Mat3& E = *Eopt;

    int ninl = 0;
    double cost = 0.0;
    std::vector<bool> mask(N, false);

    for (int i = 0; i < N; ++i) {
      const double x0 = norm.x0[i][0];
      const double y0 = norm.x0[i][1];
      const double x1 = norm.x1[i][0];
      const double y1 = norm.x1[i][1];
      const double e2 = SampsonErrorSq(E, x0, y0, x1, y1);
      if (e2 < th2) {
        mask[i] = true;
        ninl++;
        cost += e2;
      }
    }

    if (ninl > best_inliers || (ninl == best_inliers && cost < best_cost)) {
      best_inliers = ninl;
      best_cost = cost;
      bestE = E;
      best_mask.swap(mask);
    }
  }

  if (best_inliers < 8) {
    return std::nullopt;
  }

  EstimationOutput out;
  out.model.type = "E";
  out.model.mat3x3 = {
      bestE[0][0], bestE[0][1], bestE[0][2], bestE[1][0], bestE[1][1],
      bestE[1][2], bestE[2][0], bestE[2][1], bestE[2][2],
  };
  out.inliers = std::move(best_mask);
  return out;
}

}  // namespace

ErrorCode RunLegacyMonolith(const std::string& input_path,
                            const std::string& output_path) {
  // NOTE: legacy must NOT print stderr; main decides what to print.
  std::string text;
  if (!ReadAll(input_path, &text)) {
    return ErrorCode::kInvalidJson;
  }

  nlohmann::json j;
  try {
    j = nlohmann::json::parse(text);
  } catch (...) {
    return ErrorCode::kInvalidJson;
  }

  ErrorCode err = ErrorCode::kOk;
  auto parsed = ParseAndValidate(j, &err);
  if (!parsed.has_value()) {
    return err;  // kInvalidSchema
  }
  const PairInput& in = parsed->in;

  NormalizedPair norm = Normalize(in);

  auto est = EstimateEssentialRansac(in, norm);
  if (!est.has_value()) {
    return ErrorCode::kEstimationFailed;
  }
  if (est->inliers.size() != in.matches.size()) {
    return ErrorCode::kEstimationFailed;
  }

  Metrics m;
  m.num_matches = static_cast<int>(in.matches.size());
  m.num_inliers = 0;
  for (bool b : est->inliers) {
    if (b) {
      m.num_inliers++;
    }
  }
  m.inlier_ratio = (m.num_matches > 0)
                       ? (static_cast<double>(m.num_inliers) / m.num_matches)
                       : 0.0;
  m.median_sampson_error = MedianSampsonError(norm, est->model, est->inliers);

  Decision d = Decide(m);

  // IMPORTANT: write output for both ACCEPT and REJECT once estimation succeeded.
  nlohmann::json outj = ToJson(*est, m, d);
  if (!WriteAll(output_path, outj.dump(2))) {
    // treat as invalid_json IO error (you can introduce kIoError if you want; spec doesn't)
    return ErrorCode::kInvalidJson;
  }

  return (d == Decision::kAccept) ? ErrorCode::kOk : ErrorCode::kRejected;
}

}  // namespace nitr::case004
