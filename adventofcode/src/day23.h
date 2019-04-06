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
	};
	int Part1(std::vector<Point> points);
}
