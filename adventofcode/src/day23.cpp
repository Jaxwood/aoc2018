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

	bool Cube::withinCube(Point &point) {
		return
			point.xCoord() < this->max.xCoord() &&
			point.yCoord() < this->max.yCoord() &&
			point.zCoord() < this->max.zCoord() &&
			point.xCoord() > this->min.xCoord() &&
			point.yCoord() > this->min.yCoord() &&
			point.zCoord() > this->min.zCoord();
	}

	Point Cube::closestPoint(Point &point) {
		int x, y, z;
		// x
		if(point.xCoord() > this->max.xCoord()) {
			x = this->max.xCoord();
		}
		else if (point.xCoord() < this->min.xCoord()) {
			x = this->min.xCoord();
		}
		else {
			x = point.xCoord();
		}
		// y
		if(point.yCoord() > this->max.yCoord()) {
			y = this->max.yCoord();
		}
		else if (point.yCoord() < this->min.yCoord()) {
			y = this->min.yCoord();
		}
		else {
			y = point.yCoord();
		}
		// z
		if(point.zCoord() > this->max.zCoord()) {
			z = this->max.zCoord();
		}
		else if (point.zCoord() < this->min.zCoord()) {
			z = this->min.zCoord();
		}
		else {
			z = point.zCoord();
		}
		return Point(x, y, z, point.radius());
	}

	bool Cube::inRange(Point &point) {
		if (this->withinCube(point)) {
			return true;
		}
		auto closestPoint = this->closestPoint(point);
		return closestPoint.isInRangeOf(point);
	}

	bool Cube::isPoint() {
		return this->min == this->max;
	}

	int Cube::distanceToOrigin() {
		auto origin = Point(0, 0, 0, 0);
		return this->min.distanceTo(origin);
	}

	int Part2(vector<Point> points) {
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

		auto compare = [](const tuple<Cube,int> &n1, const tuple<Cube,int> &n2) -> bool {
			int first, second;
			Cube c1, c2;
			tie(c1, first) = n1;
			tie(c2, second) = n2;
			return first > second;
		};

		int bestGuess = 0;
		vector<Cube> bestGuesses;
		auto bestCube = Cube(Point(xMin, yMin, zMin, 0), Point(xMax, yMax, zMax, 0));
		priority_queue<tuple<Cube,int>, vector<tuple<Cube,int>>, decltype(compare)> cubesToCheck(compare);
		cubesToCheck.push(make_tuple(bestCube, points.size()));

		while (!cubesToCheck.empty()) {
			int total; Cube quadrant;
			tie(quadrant, total) = cubesToCheck.top(); cubesToCheck.pop();
			if (total < bestGuess) {
				continue;
			}
			// divide candidate cube into 8 evenly sized cubes
			auto cubes = quadrant.divide();

			// for each cube find bots in range
			for (auto &cube : cubes) {
				auto count = count_if(begin(points), end(points), [&cube](Point &point) {
					return cube.inRange(point);
				});
				// as an optimization the bestGuess can be hardcoded to a high number
				// to lower the runtime of the algorithm
				if (!cube.isPoint() && count > bestGuess)
				{
					cubesToCheck.push(make_tuple(cube, count));
				}
				// store best match
				if (cube.isPoint() && count > bestGuess) {
					bestGuess = count;
					bestCube = cube;
					bestGuesses.clear();
				}
				// store multiple matches
				if (cube.isPoint() && count == bestGuess) {
					bestGuesses.push_back(cube);
				}
			}
		}
		auto shortestDistanceToOrigin = INT32_MAX;
		for (auto &guess : bestGuesses) {
			if (guess.distanceToOrigin() < shortestDistanceToOrigin) {
				shortestDistanceToOrigin = guess.distanceToOrigin();
				bestCube = guess;
			}
		}
		return bestCube.distanceToOrigin();
	}
}
