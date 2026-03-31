#include "math_linalg.h"

#include <algorithm>

namespace nitr::case004 {

static inline void SortEigenAscending3(SymEigen<3>* e) {
  // sort by eigenvalue ascending; swap columns of v accordingly
  int idx[3] = {0, 1, 2};
  std::sort(idx, idx + 3, [&](int a, int b) { return e->d[a] < e->d[b]; });

  double d2[3];
  double v2[3][3];
  for (int j = 0; j < 3; ++j) {
    d2[j] = e->d[idx[j]];
    for (int r = 0; r < 3; ++r) {
      v2[r][j] = e->v[r][idx[j]];
    }
  }
  for (int j = 0; j < 3; ++j) {
    e->d[j] = d2[j];
    for (int r = 0; r < 3; ++r) {
      e->v[r][j] = v2[r][j];
    }
  }
}

// -------------------- 3x3 SVD via eigen of A^T A --------------------
static inline Mat3 MatFromCols(const Vec3& c0, const Vec3& c1, const Vec3& c2) {
  Mat3 M;
  M[0][0] = c0[0];
  M[1][0] = c0[1];
  M[2][0] = c0[2];
  M[0][1] = c1[0];
  M[1][1] = c1[1];
  M[2][1] = c1[2];
  M[0][2] = c2[0];
  M[1][2] = c2[1];
  M[2][2] = c2[2];
  return M;
}

static inline Vec3 Col(const Mat3& M, int j) {
  return Vec3{{M[0][j], M[1][j], M[2][j]}};
}

static inline Mat3 Diag3(double s0, double s1, double s2) {
  Mat3 D;
  D[0][0] = s0;
  D[1][1] = s1;
  D[2][2] = s2;
  return D;
}

static inline Mat3 OrthonormalizeCols(const Mat3& V) {
  // simple Gram-Schmidt
  Vec3 c0 = Col(V, 0);
  Vec3 c1 = Col(V, 1);
  Vec3 c2 = Col(V, 2);

  auto norm = [](const Vec3& a) { return std::sqrt(Dot(a, a)); };
  auto scale = [](const Vec3& a, double s) {
    return Vec3{{a[0] * s, a[1] * s, a[2] * s}};
  };
  auto sub = [](const Vec3& a, const Vec3& b) {
    return Vec3{{a[0] - b[0], a[1] - b[1], a[2] - b[2]}};
  };

  double n0 = norm(c0);
  if (n0 > 0) {
    c0 = scale(c0, 1.0 / n0);
  }

  // c1 -= (c0·c1)c0
  c1 = sub(c1, scale(c0, Dot(c0, c1)));
  double n1 = norm(c1);
  if (n1 > 0) {
    c1 = scale(c1, 1.0 / n1);
  }

  // c2 -= (c0·c2)c0 + (c1·c2)c1
  c2 = sub(c2, scale(c0, Dot(c0, c2)));
  c2 = sub(c2, scale(c1, Dot(c1, c2)));
  double n2 = norm(c2);
  if (n2 > 0) {
    c2 = scale(c2, 1.0 / n2);
  }

  return MatFromCols(c0, c1, c2);
}

Mat3 EnforceRank2Essential(const Mat3& E) {
  // Compute eigen of E^T E => V, singular values sqrt(eigs)
  Mat3 Et = Transpose(E);
  Mat3 B = Mul(Et, E);

  double A3[3][3];
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      A3[r][c] = B[r][c];
    }
  }
  auto eig = JacobiEigenSymmetric<3>(A3);
  SortEigenAscending3(&eig);

  // V columns are eigenvectors
  Mat3 V;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      V[r][c] = eig.v[r][c];
    }
  }
  V = OrthonormalizeCols(V);

  double s[3];
  for (int i = 0; i < 3; ++i) {
    s[i] = (eig.d[i] > 0.0) ? std::sqrt(eig.d[i]) : 0.0;
  }
  // sort ascending already: s[0] smallest, s[2] largest.
  // Essential rank-2 => smallest singular = 0, and usually first two equal.
  // We'll do: set s0=0, keep s1,s2 but also enforce s1==s2 by average of the two largest.
  double a = 0.5 * (s[1] + s[2]);
  double s0 = 0.0, s1 = a, s2 = a;

  // U = E V S^{-1}
  Mat3 EV = Mul(E, V);
  Mat3 Sinv =
      Diag3((s0 > 1e-15) ? (1.0 / s0) : 0.0, (s1 > 1e-15) ? (1.0 / s1) : 0.0,
            (s2 > 1e-15) ? (1.0 / s2) : 0.0);
  Mat3 U = Mul(EV, Sinv);
  U = OrthonormalizeCols(U);

  Mat3 Snew = Diag3(s0, s1, s2);
  Mat3 Ut = Transpose(U);
  Mat3 E2 = Mul(Mul(U, Snew), Transpose(V));

  return E2;
}
}  // namespace nitr::case004
