#pragma once

#include <string>
#include <vector>

using namespace std;

namespace Day10 {
	class Point {
	private:
		int x, y, incX, incY;
	public:
		Point(int x, int y, int incX, int incY) {
			this->x = x;
			this->y = y;
			this->incX = incX;
			this->incY = incY;
		}
	};
	string Part1(vector<Point> points);
}
