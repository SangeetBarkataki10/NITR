#pragma once

#include <cmath>

namespace nitr::case004 {

// -------------------- small linalg --------------------
struct Vec3 {
  double v[3] = {0, 0, 0};
  double& operator[](int i) {
    return v[i];
  }
  double operator[](int i) const {
    return v[i];
  }
};

struct Mat3 {
  double m[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double* operator[](int r) {
    return m[r];
  }
  const double* operator[](int r) const {
    return m[r];
  }
};

static inline Mat3 Transpose(const Mat3& A) {
  Mat3 T;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      T[r][c] = A[c][r];
    }
  }
  return T;
}

static inline Vec3 Mul(const Mat3& A, const Vec3& x) {
  Vec3 y;
  for (int r = 0; r < 3; ++r) {
    y[r] = A[r][0] * x[0] + A[r][1] * x[1] + A[r][2] * x[2];
  }
  return y;
}

static inline Mat3 Mul(const Mat3& A, const Mat3& B) {
  Mat3 C;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      C[r][c] = 0.0;
      for (int k = 0; k < 3; ++k) {
        C[r][c] += A[r][k] * B[k][c];
      }
    }
  }
  return C;
}

static inline double Dot(const Vec3& a, const Vec3& b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

static inline Mat3 Identity3() {
  Mat3 I;
  I[0][0] = 1.0;
  I[1][1] = 1.0;
  I[2][2] = 1.0;
  return I;
}

// -------------------- Jacobi eigen (symmetric) for NxN --------------------
template <int N>
struct SymEigen {
  double d[N];     // eigenvalues
  double v[N][N];  // eigenvectors as columns: v[row][col]
};

// Jacobi eigen decomposition for symmetric matrix A (in-place copy).
template <int N>
static SymEigen<N> JacobiEigenSymmetric(double A[N][N]) {
  SymEigen<N> out;
  // init V = I
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      out.v[r][c] = (r == c) ? 1.0 : 0.0;
    }
  }

  const int kMaxSweeps = 60;
  const double eps = 1e-12;

  for (int sweep = 0; sweep < kMaxSweeps; ++sweep) {
    // find largest off-diagonal element
    int p = 0, q = 1;
    double max_off = 0.0;
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        double a = std::fabs(A[i][j]);
        if (a > max_off) {
          max_off = a;
          p = i;
          q = j;
        }
      }
    }
    if (max_off < eps) {
      break;
    }

    const double app = A[p][p];
    const double aqq = A[q][q];
    const double apq = A[p][q];

    // compute Jacobi rotation
    double tau = (aqq - app) / (2.0 * apq);
    double t;
    if (tau >= 0.0) {
      t = 1.0 / (tau + std::sqrt(1.0 + tau * tau));
    } else {
      t = -1.0 / (-tau + std::sqrt(1.0 + tau * tau));
    }
    const double c = 1.0 / std::sqrt(1.0 + t * t);
    const double s = t * c;

    // rotate A: zero out A[p][q]
    A[p][p] = app - t * apq;
    A[q][q] = aqq + t * apq;
    A[p][q] = 0.0;
    A[q][p] = 0.0;

    for (int k = 0; k < N; ++k) {
      if (k == p || k == q) {
        continue;
      }
      const double aik = A[k][p];
      const double akq = A[k][q];

      const double new_kp = c * aik - s * akq;
      const double new_kq = s * aik + c * akq;

      A[k][p] = new_kp;
      A[p][k] = new_kp;
      A[k][q] = new_kq;
      A[q][k] = new_kq;
    }

    // update eigenvectors V
    for (int k = 0; k < N; ++k) {
      const double vip = out.v[k][p];
      const double viq = out.v[k][q];
      out.v[k][p] = c * vip - s * viq;
      out.v[k][q] = s * vip + c * viq;
    }
  }

  for (int i = 0; i < N; ++i) {
    out.d[i] = A[i][i];
  }
  return out;
}

Mat3 EnforceRank2Essential(const Mat3& E);

}  // namespace nitr::case004
