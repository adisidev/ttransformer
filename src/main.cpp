#include "point.hpp"
#include "ttransformer.hpp"
#include <iostream>

int main(void)
{

    std::array<Point, 3> org_tri, tri;
    double temp_x, temp_y;  // Temporary variables to store input coordinates

    std::cout << "Enter original triangle points (x y):" << std::endl;
    for (auto &p : org_tri) {
      std::cin >> temp_x >> temp_y;  // Store inputs in temporary variables
      p = Point(temp_x, temp_y);
    }

    std::cout << "Enter new triangle points (x y):" << std::endl;
    for (auto &p : tri) {
      std::cin >> temp_x >> temp_y;  // Store inputs in temporary variables
      p = Point(temp_x, temp_y);
    }

  while (true) {
    std::cout << "Enter point to be transformed (x y):" << std::endl;
    std::cin >> temp_x >> temp_y;  // Store inputs in temporary variables
    Point pt = Point(temp_x, temp_y);

    Point transformed_point = affine_transf(tri, org_tri, pt);
    std::cout << "Transformed point: (" << transformed_point.x() << ", " << transformed_point.y() << ")" << std::endl;
  }
  return 0;
}