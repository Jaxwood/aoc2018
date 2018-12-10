#include "Day10.h"


namespace Day10 {

	tuple<int, int, int, int> boundaries(vector<Point> points) {
		auto maxX = max_element(begin(points), end(points), [](Point p1, Point p2) {
			return p1.xCoord() < p2.xCoord();
		});
		auto maxY = max_element(begin(points), end(points), [](Point p1, Point p2) {
			return p1.yCoord() < p2.yCoord();
		});
		auto minX = min_element(begin(points), end(points), [](Point p1, Point p2) {
			return p1.xCoord() < p2.xCoord();
		});
		auto minY = min_element(begin(points), end(points), [](Point p1, Point p2) {
			return p1.yCoord() < p2.yCoord();
		});
		return make_tuple((*minX).xCoord(), (*maxX).xCoord(), (*minY).yCoord(), (*maxY).yCoord());
	}

	vector<string> draw(vector<Point> points, int minX, int minY, int maxX, int maxY) {
		vector<string> result;

		for (int y = minY; y <= maxY; y++) {
			string target = "";
			for (int x = minX; x <= maxX; x++) {
				if (count_if(begin(points), end(points), [x, y](Point p1) { return p1.xCoord() == x && p1.yCoord() == y; }) > 0)
				{
					target.push_back('#');
				}
				else {
					target.push_back('.');
				}
			}
			result.push_back(target);
		}

		return result;
	}

	vector<string> Part1(vector<Point> points, int seconds) {
		vector<string> result;
		int maxX, maxY, minX, minY = 0;
		for (int i = 0; i < seconds; i++) {
			for (auto &point : points) {
				point.tick();
			}
		}
		tie(minX, maxX, minY, maxY) = boundaries(points);
		result = draw(points, minX, minY, maxX, maxY);
		return result;
	}
}
