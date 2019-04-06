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
		int sum() {
			return this->x + this->y + this->z;
		}
	};
	int Part1(std::vector<Point> points);
}
