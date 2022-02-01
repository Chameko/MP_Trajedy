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

  // Reverse * op
  Point operator*(const double& d, const Point& p) {
    Point point;
    point.x = p.x * d;
    point.y = p.y * d;
    return point;
  }

  double distance(const Point& p1, const Point& p2) {
      double a = (p1.x - p2.x);
      double b = (p1.y - p2.y);
      double dist = sqrt(a * a + b * b);
      return dist;
  }
}