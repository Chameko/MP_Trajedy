#include "Catwalk.h"
#include <iostream>

namespace mp_trajedy {
  Catwalk::Catwalk(std::vector<Point> points, Point ctrlP1, Point ctrlP2) {
    _points = points;
    _ctrlP1 = ctrlP1;
    _ctrlP2 = ctrlP2;
    _segments = genSegments(_points, _ctrlP1, _ctrlP2);
    _totalLength = _segments[_segments.size() - 1].totalLength;
  }

  std::vector<Catwalk::Segment> Catwalk::genSegments(std::vector<Point> points, Point ctrlP1, Point ctrlP2) {
    std::vector<Segment> segments;

    // Append the control points in the appropriate places in the vector
    points.push_back(ctrlP2);
    points.insert(points.begin(), ctrlP1);

    // The total length of the spline
    double totalLength = 0;

    for (int i = 0; i < points.size() - 3; i++ ) {
      // Generate a segment from the array of control points
      Segment seg = genSegment(points[i], points[i + 1], points[i + 2], points[i + 3], totalLength);

      // Update variables
      totalLength = seg.totalLength;
      segments.push_back(seg);
    }

    return segments;
  }

  Catwalk::Segment Catwalk::genSegment(Point p1, Point p2, Point p3, Point p4, double totalLength) {
    Segment seg;
    seg.p1 = p1;
    seg.p2 = p2;
    seg.p3 = p3;
    seg.p4 = p4;
    seg.segmentLength = calcSegmentLength(seg);
    seg.totalLength = totalLength + seg.segmentLength;

    return seg;
  }

  double Catwalk::calcSegmentLength(Segment seg) {
    double segLength = 0;
    Point oldPoint = seg.p2;
    Point newPoint;

    // Step through
    for (double t = 0;t <= 1; t += _stepSize) {
      double tt = t * t;
      double ttt = tt * t;

      double b1 = 0.5 * (-ttt + 2*tt - t);
      double b2 = 0.5 * (3*ttt - 5*tt + 2);
      double b3 = 0.5 * (-3*ttt + 4*tt + t);
      double b4 = 0.5 * (ttt - tt);

      newPoint = seg.p1 * b1 + seg.p2 * b2 + seg.p3 * b3 + seg.p4 * b4;

      segLength += distance(oldPoint, newPoint);

      oldPoint = newPoint;
    }

    return segLength;
  }

  Point Catwalk::getGradientPoint(double dist) {
    int segmentIndex = getSegmentFromDistance(dist);

    Segment seg = _segments[segmentIndex];

    // Get the distance as a ratio of the segment's length
    double t = (dist - _segments[segmentIndex - 1].totalLength) / seg.segmentLength;

    // Maths from https://lucidar.me/en/mathematics/catmull-rom-splines/
    // Matrix pre-multiplied out, T = 0.5

    double tt = t * t;

    double c1 = 0.5 * (-1 + 4*t - 3*tt);
    double c2 = 0.5 * (-10*t + 9*tt);
    double c3 = 0.5 * (1 + 8*t - 9*tt);
    double c4 = 0.5 * (-2*t + 3*tt);

    Point m = c1 * seg.p1 + c2 * seg.p2 + c3 * seg.p3 + c4 * seg.p4;

    return m;
  }

  double Catwalk::getAngleRad(double dist) {
    Point gradient = getGradientPoint(dist);
    return atan2(gradient.y, gradient.x);
  }

  double Catwalk::getAngleDeg(double dist) {
    return getAngleRad(dist) * (180/M_PI);
  }

  int Catwalk::getSegmentFromDistance(double dist) {
    // Index
    int segmentIndex = 0;
    // Total length of first segment
    double totalLength = _segments[0].totalLength;

    // Grab the correct segment
    // Loops through all segments in our spline
    for (int i = 0; i < _segments.size(); i++) {
      // if The distance is within segment i
      if (_segments[i].totalLength >= dist) {
        // Grab the index and we still are following the spline
        segmentIndex = i;
        _status = Status::kFollowing;
        break;
      } else {
        // Grab the index. If the loop has gone through the list then we have complete the spline, hence status is set to complete here.
        _status = Status::kComplete;
        segmentIndex = i;
      }
    }

    // Return index
    return segmentIndex;
  }

  Point Catwalk::getPoint(double dist) {
    int segmentIndex = getSegmentFromDistance(dist);

    Segment seg = _segments[segmentIndex];

    // Get the distance as a ratio of the segment's length
    double t = (dist - _segments[segmentIndex - 1].totalLength) / seg.segmentLength;

    // Maths from https://lucidar.me/en/mathematics/catmull-rom-splines/
    // Matrix pre-multiplied out, T = 0.5

    double tt = t * t;
    double ttt = tt * t;

    double b1 = 0.5 * (-ttt + 2*tt - t);
    double b2 = 0.5 * (3*ttt - 5*tt + 2);
    double b3 = 0.5 * (-3*ttt + 4*tt + t);
    double b4 = 0.5 * (ttt - tt);

    Point point = seg.p1 * b1 + seg.p2 * b2 + seg.p3 * b3 + seg.p4 * b4;

    return point;
  }
}