#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
namespace Day23 {
	class Point {
	private:
		int x, y, z, r;
	public:
		Point() {};
		Point(int x, int y, int z, int r) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->r = r;
		}
		int radius() {
			return this->r;
		}
		int distanceTo(Point &point) {
			return (abs(this->x - point.x) + abs(this->y - point.y) + abs(this->z - point.z));
		}
		bool isInRangeOf(Point point) {
			return point.radius() >= this->distanceTo(point);
		}
		int xCoord() {
			return this->x;
		}
		int yCoord() {
			return this->y;
		}
		int zCoord() {
			return this->z;
		}
		bool operator<(const Point &point) const {
			if (this->x != point.x) {
				return this->x < point.x;
			}
			if (this->y != point.y) {
				return this->y < point.y;
			}
			if (this->z != point.z) {
				return this->z < point.z;
			}
			return this->r < point.r;
		}
		bool operator!=(const Point &point) const {
			return this->x != point.x || this->y != point.y || this->z != point.z || this->r != point.r;
		}
		bool operator==(const Point &point) const {
			return this->x == point.x && this->y == point.y && this->z == point.z && this->r == point.r;
		}
	};

	class Cube {
		Point min;
		Point max;
		bool withinCube(Point &point);
		Point closestPoint(Point &point);
	public:
		Cube(Point min, Point max) {
			this->min = min;
			this->max = max;
		}
		std::vector<Cube> divide();
		bool inRange(Point &point);
		bool isPoint();
		int distanceToOrigin();

		bool operator<(const Cube &cube) const {
			if (this->min != cube.min) {
				return this->min < cube.min;
			}

			return this->max < cube.max;
		}
		bool operator==(const Cube &other) const {
			return this->min == other.min && this->max == other.max;
		}
	};
	int Part1(std::vector<Point> points);
	int Part2(std::vector<Point> points);
}
