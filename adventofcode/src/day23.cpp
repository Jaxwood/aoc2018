#include "Day23.h"

using namespace std;

namespace Day23 {
	int nanobotsInRangeCount(vector<Point> points, Point point) {
		return count_if(points.begin(), points.end(), [&point](Point &other) {
			return other.isInRangeOf(point);
		});
	}

	int distance(Coordinate coord) {
		int x, y, z;
		tie(x, y, z) = coord;
		return abs(x - 0) + abs(y - 0) + abs(z - 0);
	}

	int Part1(vector<Point> points) {
		auto maxRadiusPoint = *max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.radius() < p2.radius();
		});
		return nanobotsInRangeCount(points, maxRadiusPoint);
	}

	int Part2(vector<Point> points) {
		map<Coordinate, int> nanobotCounts;

		// the the boundaries of the coordinates
		auto maxX = (*max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.xCoord() < p2.xCoord();
		})).xCoord();
		auto minX = (*min_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.xCoord() < p2.xCoord();
		})).xCoord();
		auto maxY = (*max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.yCoord() < p2.yCoord();
		})).yCoord();
		auto minY = (*min_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.yCoord() < p2.yCoord();
		})).yCoord();
		auto maxZ = (*max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.zCoord() < p2.zCoord();
		})).zCoord();
		auto minZ = (*min_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.zCoord() < p2.zCoord();
		})).zCoord();

		// loop through all coordinates and calculate the nanobots in range
		for (auto x = minX; x <= maxX; x++) {
			for (auto y = minY; y <= maxY; y++) {
				for (auto z = minZ; z <= maxZ; z++) {
					auto coord = make_tuple(x, y, z);
					auto count = count_if(points.begin(), points.end(), [&coord](Point &other) {
						return other.isInRangeOf(coord);
					});
					nanobotCounts[coord] = count;
				}
			}
		}

		// get the highest nanobot count in range
		auto maxNanobotInRange = (*max_element(nanobotCounts.begin(), nanobotCounts.end(), [](const pair<Coordinate, const int> p1, pair<Coordinate, int> p2) {
			return p1.second < p2.second;
		})).second;

		// copy all coordinates that matches the highest count
		vector<pair<Coordinate, int>> result;
		auto maxes = copy_if(nanobotCounts.begin(), nanobotCounts.end(), back_inserter(result), [&maxNanobotInRange](const pair<Coordinate,int> coord) {
			return coord.second == maxNanobotInRange;
		});

		// sort by how close it is to (0,0,0)
		sort(result.begin(), result.end(), [](pair<Coordinate, int> c1, pair<Coordinate, int> c2) {
			int x, y, z;
			tie(x, y, z) = c1.first;
			auto d1 = abs(x) + abs(y) + abs(z);
			tie(x, y, z) = c2.first;
			auto d2 = abs(x) + abs(y) + abs(z);
			return d1 < d2;
		});

		// get the manhattan distance to the first element in the sorted range
		return distance(result[0].first);
	}
}
