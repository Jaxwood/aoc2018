#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
namespace Day23 {
	typedef std::tuple<int, int, int> Coordinate;
	class Point {
	private:
		int x, y, z, r;
	public:
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
		bool isInRangeOf(Coordinate coordinate) {
			int x, y, z;
			std::tie(x, y, z) = coordinate;
			return this->radius() >= (abs(this->x - x) + abs(this->y - y) + abs(this->z - z));
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
		Coordinate asCoordinate() {
			return std::make_tuple(this->x, this->y, this->z);
		}
	};
	int Part1(std::vector<Point> points);
	int Part2(std::vector<Point> points);
}
