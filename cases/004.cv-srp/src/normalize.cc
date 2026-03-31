#include "normalize.h"

namespace nitr::case004 {

NormalizedPair NormalizeMatches(const PairInput& in) {
  NormalizedPair out;
  out.x0.reserve(in.matches.size());
  out.x1.reserve(in.matches.size());

  for (const auto& m : in.matches) {
    const auto& p0 = in.f0.keypoints_px[m.i0];
    const auto& p1 = in.f1.keypoints_px[m.i1];

    const double x0 = (p0[0] - in.cam.cx) / in.cam.fx;
    const double y0 = (p0[1] - in.cam.cy) / in.cam.fy;
    const double x1 = (p1[0] - in.cam.cx) / in.cam.fx;
    const double y1 = (p1[1] - in.cam.cy) / in.cam.fy;

    out.x0.push_back({x0, y0});
    out.x1.push_back({x1, y1});
  }
  return out;
}

}  // namespace nitr::case004
