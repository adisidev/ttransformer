#ifndef TTRANSFORMER_HPP_
#define TTRANSFORMER_HPP_

#include "point.hpp"
#include "matrix.hpp"
#include <array>

Point affine_transf(
  const std::array<Point, 3> &tri,
  const std::array<Point, 3> &org_tri,
  const Point &pt);

#endif