#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

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

		void tick() {
			this->x += incX;
			this->y += incY;
		}

		int xCoord() {
			return this->x;
		}

		int yCoord() {
			return this->y;
		}
	};
	vector<string> Part1(vector<Point> points, int seconds);
}
