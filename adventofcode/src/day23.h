#include <algorithm>
#include <vector>
namespace Day23 {
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
	};
	int Part1(std::vector<Point> points);
}
