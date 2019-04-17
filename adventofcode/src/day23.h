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
		bool isInRangeOf(Point point) {
			return point.radius() >= (abs(this->x - point.x) + abs(this->y - point.y) + abs(this->z - point.z));
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
			return this->x != point.x && this->y != point.y && this->z != point.z && this->r != point.r;
		}
	};

	class Cube {
		Point min;
		Point max;
	public:
		Cube(Point min, Point max) {
			this->min = min;
			this->max = max;
		}
		std::vector<Cube> divide();
		bool inRange(Point &point);

		bool operator<(const Cube &cube) const {
			if (this->min != cube.min) {
				return this->min < cube.min;
			}

			return this->max < cube.max;
		}
	};
	int Part1(std::vector<Point> points);
	int Part2(std::vector<Point> points);
}
