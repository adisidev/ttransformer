#include "ttransformer.hpp"

Point affine_transf(
  const std::array<Point, 3> &tri,
  const std::array<Point, 3> &org_tri,
  const Point &pt)
{
  // For each point, we make the following transformation. Suppose we find
  // that, before the cartogram transformation, a point (x, y) is in the
  // triangle (a, b, c). We want to find its position in the projected
  // triangle (p, q, r). We locally approximate the cartogram transformation
  // by an affine transformation T such that T(a) = p, T(b) = q and T(c) = r.
  // We can think of T as a 3x3 matrix
  //    -----------
  //   |t11 t12 t13|
  //   |t21 t22 t23|  such that
  //   | 0   0   1 |
  //    -----------
  //    -----------   ----------     ----------
  //   |t11 t12 t13| | a1 b1 c1 |   | p1 q1 r1 |
  //   |t21 t22 t23| | a2 b2 c2 | = | p2 q2 r2 | or TA = P.
  //   | 0   0   1 | | 1  1  1  |   |  1  1  1 |
  //    -----------   ----------     ----------
  // Hence, T = PA^{-1}.
  //                              -----------------------
  //                             |b2-c2 c1-b1 b1*c2-b2*c1|
  // We have A^{-1} = (1/det(A)) |c2-a2 a1-c1 a2*c1-a1*c2|. By multiplying
  //                             |a2-b2 b1-a1 a1*b2-a2*b1|
  //                              -----------------------
  // PA^{-1} we obtain t11, t12, t13, t21, t22, and t23. If the original
  // coordinates are (x, y) on the unprojected map, then the transformed
  // coordinates are:
  // post.x = t11*x + t12*y + t13, post.y = t21*x + t22*y + t23.
  const Point pre(pt.x(), pt.y());

  // Old triangle (a, b, c) expressed as matrix A
  const Matrix abc_mA(org_tri[0], org_tri[1], org_tri[2]);

  // New triangle (p, q, r) expressed as matrix P
  const Matrix pqr_mP(tri[0], tri[1], tri[2]);

  // Transformation matrix T
  const auto mT = pqr_mP.multiplied_with(abc_mA.inverse());

  // Transformed point
  return mT.transformed_point(pre);
}