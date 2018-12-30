#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

namespace Day15 {

	typedef std::tuple<int, int> Point;

	class Atlas {
		const int size = 10;
		const char OPEN = '.';
		char grid[10][10];
	public:
		void initialize(std::vector<std::string> raw);
		bool equal(const Atlas &other) const;
		void swap(Point p1, Point p2);
		void clear(Point point);
		std::vector<Point> neighbors(Point point) const;
		std::vector<Point> types(const char c) const;
	};

	bool operator==(const Atlas &a1, const Atlas &a2);

	class PathFinder {
	};

	int Part1(std::vector<std::string> lines);
}
