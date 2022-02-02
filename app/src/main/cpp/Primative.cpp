#include "Primative.h"

namespace mp_trajedy {
  double distance(const Point& p1, const Point& p2) {
    double a = (p1.x - p2.x);
    double b = (p1.y - p2.y);
    double dist = sqrt(a * a + b * b);
    return dist;
  }

  Point operator*(const double& d, const Point& p) {
    Point point;
    point.x = p.x * d;
    point.y = p.y * d;
    return point;
  }
}