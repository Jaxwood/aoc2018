#include "Day23.h"

using namespace std;

namespace Day23 {
	int nanobotsInRangeCount(vector<Point> points, Point point) {
		return count_if(points.begin(), points.end(), [&point](Point &other) {
			return other.isInRangeOf(point);
		});
	}

	int Part1(vector<Point> points) {
		auto maxRadiusPoint = *max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.radius() < p2.radius();
		});
		return nanobotsInRangeCount(points, maxRadiusPoint);
	}

	vector<Cube> Cube::divide() {
		auto xSize = this->max.xCoord() - this->min.xCoord();
		auto ySize = this->max.yCoord() - this->min.yCoord();
		auto zSize = this->max.zCoord() - this->min.zCoord();

		// might cause an edge condition in the end
		if (xSize % 2 != 0) xSize -= 1;
		if (ySize % 2 != 0) ySize -= 1;
		if (zSize % 2 != 0) zSize -= 1;
		auto xLength = xSize / 2;
		auto yLength = ySize / 2;
		auto zLength = zSize / 2;

		auto q1 = Cube(Point(this->max.xCoord() - xLength, this->max.yCoord() - yLength, this->max.zCoord() - zLength, 0), Point(this->max.xCoord(), this->max.yCoord(), this->max.zCoord(), 0));
		auto q2 = Cube(Point(this->max.xCoord() - xLength, this->max.yCoord() - (2 * yLength), this->max.zCoord() - zLength, 0), Point(this->max.xCoord(), this->max.yCoord() - yLength, this->max.zCoord(), 0));
		auto q3 = Cube(Point(this->max.xCoord() - (2 * xLength), this->max.yCoord() - (2 * yLength), this->max.zCoord() - zLength, 0), Point(this->max.xCoord() - xLength, this->max.yCoord() - yLength, this->max.zCoord(), 0));
		auto q4 = Cube(Point(this->max.xCoord() - (2 * xLength), this->max.yCoord() - yLength, this->max.zCoord() - zLength, 0), Point(this->max.xCoord() - xLength, this->max.yCoord(), this->max.zCoord(), 0));
		auto q5 = Cube(Point(this->max.xCoord() - xLength, this->max.yCoord() - yLength, this->max.zCoord() - (2 * zLength), 0), Point(this->max.xCoord(), this->max.yCoord(), this->max.zCoord() - zLength, 0));
		auto q6 = Cube(Point(this->max.xCoord() - xLength, this->max.yCoord() - (2 * yLength), this->max.zCoord() - (2 * zLength), 0), Point(this->max.xCoord(), this->max.yCoord() - yLength, this->max.zCoord() - zLength, 0));
		auto q7 = Cube(Point(this->max.xCoord() - (2 * xLength), this->max.yCoord() - (2 * yLength), this->max.zCoord() - (2 * zLength), 0), Point(this->max.xCoord() - xLength, this->max.yCoord() - yLength, this->max.zCoord() - zLength, 0));
		auto q8 = Cube(Point(this->max.xCoord() - (2 * xLength), this->max.yCoord() - yLength, this->max.zCoord() - (2 * zLength), 0), Point(this->max.xCoord() - xLength, this->max.yCoord(), this->max.zCoord() - zLength, 0));
		return vector<Cube> { q1, q2, q3, q4, q5, q6, q7, q8 };
	}

	bool Cube::inRange(Point &point) {

		bool insideCube = true;
		int x, y, z;
		// x
		if(point.xCoord() > this->max.xCoord()) {
			insideCube = false;
			x = this->max.xCoord();
		}
		else if (point.xCoord() < this->min.xCoord()) {
			insideCube = false;
			x = this->min.xCoord();
		}
		else {
			x = point.xCoord();
		}
		// y
		if(point.yCoord() > this->max.yCoord()) {
			insideCube = false;
			y = this->max.yCoord();
		}
		else if (point.yCoord() < this->min.yCoord()) {
			insideCube = false;
			y = this->min.yCoord();
		}
		else {
			y = point.yCoord();
		}
		// z
		if(point.zCoord() > this->max.zCoord()) {
			insideCube = false;
			z = this->max.zCoord();
		}
		else if (point.zCoord() < this->min.zCoord()) {
			insideCube = false;
			z = this->min.zCoord();
		}
		else {
			z = point.zCoord();
		}

		return insideCube ? true : point.isInRangeOf(Point(x, y, z, point.radius()));
	}

	bool Cube::hasSpace() {
		return this->min != this->max;
	}

	int Cube::distanceToOrigin() {
		auto origin = Point(0, 0, 0, 0);
		return this->min.distanceTo(origin);
	}

	int Part2(vector<Point> points) {
		map<Point, int> nanobotCounts;

		// the the boundaries of the Points
		auto xMax = (*max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.xCoord() < p2.xCoord();
		})).xCoord();
		auto xMin = (*min_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.xCoord() < p2.xCoord();
		})).xCoord();
		auto yMax = (*max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.yCoord() < p2.yCoord();
		})).yCoord();
		auto yMin = (*min_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.yCoord() < p2.yCoord();
		})).yCoord();
		auto zMax = (*max_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.zCoord() < p2.zCoord();
		})).zCoord();
		auto zMin = (*min_element(points.begin(), points.end(), [](Point &p1, Point &p2) {
			return p1.zCoord() < p2.zCoord();
		})).zCoord();

		// 1. divide candidate cube into 8 evenly sized cubes
		auto quadrant = Cube(Point(xMin, yMin, zMin, 0), Point(xMax, yMax, zMax, 0));
		while (quadrant.hasSpace()) {
			auto cubes = quadrant.divide();

			// 2. for each cube find bots in range
			map<Cube, int> botsInRange;
			for (auto &cube : cubes) {
				auto count = count_if(begin(points), end(points), [&cube](Point &point) {
					return cube.inRange(point);
				});
				botsInRange[cube] = count;
			}

			// 3. select cube with most bots and go to step 1
			quadrant = (*max_element(begin(botsInRange), end(botsInRange), [](const pair<Cube, int> &p1, const pair<Cube, int> &p2) {
				return p1.second < p2.second;
			})).first;
		}
		return quadrant.distanceToOrigin();
	}
}
