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
		queue<Point> candidates;
		for (auto &p1 : points) {
			vector<Point> result;
			copy_if(begin(points), end(points), back_inserter(result), [p1](Point &p2) {
				auto dist = distance(p1, p2);
				return dist > 0 && dist <= 3;
			});
			constellations[p1] = result;
		}
		candidates.push(points[0]);
		vector<vector<Point>> result = { vector<Point>() };
		int idx = 0;
		set<Point> visited;
		while (!candidates.empty()) {
			auto p = candidates.front(); candidates.pop();
			if (visited.find(p) == visited.end()) {
				result[idx].push_back(p);
			}
			visited.insert(p);
			auto nearby = constellations[p];
			for (auto &n : nearby) {
				if (visited.find(n) == visited.end()) {
					candidates.push(n);
				}
			}
			if (candidates.empty() && visited.size() != constellations.size()) {
				for (auto &m : constellations) {
					if (visited.find(m.first) == visited.end()) {
						candidates.push(m.first);
						idx++;
						result.push_back(vector<Point>());
						break;
					}
				}
			}
		}
		return result.size();
	}
}
