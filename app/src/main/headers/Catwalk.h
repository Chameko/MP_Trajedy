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

    enum Status {
      kStart,
      kFollowing,
      kComplete,
    };

    // Gets the angle given a distance
    double getAngleDeg(double dist);
    double getAngleRad(double dist);

    // Set the step size
    void setStepSize(double stepSize);

    // Get total length
    double getTotalLength() {
      return _totalLength;
    }

    // Get segment length
    double getSegmentLength(double index) {
      return _segments[index].segmentLength;
    }

    // Get a waypoint given a distance
    Point getPoint(double dist);

    // Get the status of the spline following
    Status getStatus() {
      return _status;
    }

   private:
    // Get a segment index given a distance
    int getSegmentFromDistance(double dist);

    // Status of the following
    Status _status = Status::kStart;

    // Calculate the length of a segment
    double calcSegmentLength(Segment seg);

    // Calculate the gradiant of a point
    Point getGradientPoint(double dist);

    // Generates the segments of a catmull-rom spline given an vector of points
    std::vector<Segment> genSegments(std::vector<Point> points, Point ctrlP1, Point ctrlP2);

    // Generage a segment from 4 points
    Segment genSegment(Point p1, Point p2, Point p3, Point p4, double totalLength);

    // Points of the spline
    std::vector<Point> _points;

    // Control points
    Point _ctrlP1, _ctrlP2;

    // Segments of the spline
    std::vector<Segment> _segments;

    // Total length of the spline;
    double _totalLength;

    // Step size
    double _stepSize = 0.005f;
  };
}