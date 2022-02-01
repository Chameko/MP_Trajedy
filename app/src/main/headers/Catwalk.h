#include "Primative.h"
#include <vector>

namespace mp_trajedy {
  class Catwalk {
   public:
    Catwalk(std::vector<Point> points, Point ctrlP1, Point ctrlP2);

    // Represents a segment in the spline
    struct Segment {
      Point p1, p2, p3, p4;
      double totalLength, segmentLength;
    };

    // Gets the angle given a distance
    double getAngleDeg(double dist);
    double getAngleRad(double dist);

   private:
    // Calculate the length of a segment
    double calcSegmentLength(Segment seg);

    // Calculate the gradiant of a point
    double getGradient(double dist);

    // Generates the segments of a catmull-rom spline given an vector of points
    std::vector<Segment> genSegments(std::vector<Point> points);

    // Points of the spline
    std::vector<Point> _points;

    // Segments of the spline
    std::vector<Segment> _segments;

    // Total length of the spline;
    double _totalLength;
  };
}