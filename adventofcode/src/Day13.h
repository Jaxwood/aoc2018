#pragma once

#include <tuple>
#include <vector>

using namespace std;

namespace Day13 {

	enum Direction {
		North,
		South,
		East,
		West
	};

	class Cart {
	private:
		int x, y;
		Direction direction;
	public:
		Cart(int x, int y, Direction direction) {
			this->x = x;
			this->y = y;
			this->direction = direction;
		}
	};

	tuple<int, int> Part1(vector<string> lines);

}
