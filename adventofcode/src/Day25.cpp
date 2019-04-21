#include "Day25.h"

using namespace std;

namespace Day25 {
	int distance(Point p1, Point p2) {
		int a, b, c, d, e, f, g, h;
		tie(a, b, c, d) = p1;
		tie(e, f, g, h) = p2;
		return abs(a - e) + abs(b - f) + abs(c - g) + abs(d - h);
	}

	int Part1(vector<Point> points) {
		map<Point, vector<Point>> constellations;
		for (auto i = 0; i < points.size(); i++) {
			vector<Point> result;
			auto p1 = points[i];
			copy_if(begin(points), end(points), back_inserter(result), [p1](Point &p2) {
				return distance(p1, p2) == 3;
			});
			constellations[p1] = result;
		}
		return 0;
	}
}
