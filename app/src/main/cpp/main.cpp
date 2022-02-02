#include "Catwalk.h"
#include <iostream>

using mp_trajedy::Catwalk;
using mp_trajedy::Point;

int main() {
  Point p1 = {0, 0};
  Point p2 = {1, 0};
  Point p3 = {3, 1};
  Point p4 = {4, 0};
  Point p5 = {5, 0};

  std::vector<Point> points;
  points.push_back(p2);
  points.push_back(p3);
  points.push_back(p4);

  Catwalk catwalk = Catwalk(points, p1, p5);

  double totalLength = catwalk.getTotalLength();
  double stepSize = 0.1;

  std::cout << "#####################" << std::endl << "Spline: " << std::endl << "Total length: " << catwalk.getTotalLength() << std::endl << "#####################" << std::endl;

  for (double dist = 0; dist <= totalLength; dist += stepSize) {
    std::cout << "Distance: " << dist << std::endl;
    Point p = catwalk.getPoint(dist);
    std::cout << "| Point x: " << p.x << " y: " << p.y << std::endl;
    std::cout << "| Angle: " << catwalk.getAngleDeg(dist) << std::endl;
  }

  return 0;
}