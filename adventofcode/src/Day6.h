#pragma once

#include <vector>
#include <string>

namespace Day6 {

	class Coord {
	private:

		int x;
		int y;

	public:

		Coord() {
			this->x = 0;
			this->y = 0;
		}

		Coord(int x, int y) {
			this->x = x;
			this->y = y;
		}

		int getX() {
			return this->x;
		}

		int getY() {
			return this->y;
		}

	};
	int Part1(std::vector<Coord> coords);
}
