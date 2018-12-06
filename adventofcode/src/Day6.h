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

		int getX() const {
			return this->x;
		}

		int getY() const {
			return this->y;
		}

		bool operator<(const Coord& coord) const {
			if (this->x != coord.getX()) {
				return this->x < coord.getX();
			}
			if (this->y != coord.getY()) {
				return this->y < coord.getY();
			}
			return false;
		}

	};
	int Part1(std::vector<Coord> coords);
}
