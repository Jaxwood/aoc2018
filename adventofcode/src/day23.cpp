#include "Day23.h"

using namespace std;

namespace Day23 {
	int Part1(vector<Point> points) {
		auto maxRadiusPoint = *max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.radius() < p2.radius();
		});
		auto nanobotInRangeCount = count_if(points.begin(), points.end(), [&maxRadiusPoint](Point &point) {
			return point.sum() <= maxRadiusPoint.radius();
		});
		return nanobotInRangeCount;
	}
}
