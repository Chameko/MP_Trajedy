#pragma once

#include "math.h"

namespace mp_trajedy {
  struct Point {
    double x,y;

    // Operator overloads because I don't want to type add() 50 times
    Point operator+(const Point& p) {
      Point point;
      point.x = this->x + p.x;
      point.y = this->y + p.y;
      return point;
    }

    Point operator+(const double& d) {
      Point point;
      point.x = this->x + d;
      point.y = this->y + d;
      return point;
    }

    Point operator*(const double& d) {
      Point point;
      point.x = this->x * d;
      point.y = this->y * d;
      return point;
    }

    Point operator-(const Point& p) {
      Point point;
      point.x = this->x - p.x;
      point.y = this->y - p.y;
      return point;
    }

    Point operator/(const double& d) {
      Point point;
      point.x = this->x / d;
      point.y = this->y / d;
      return point;
    }
  };

  double distance(const Point& p1, const Point& p2);

  Point operator*(const double& d, const Point& p);
}