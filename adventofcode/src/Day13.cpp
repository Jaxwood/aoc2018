#include "Day13.h"

namespace Day13 {

	bool isCart(char candidate) {
		return candidate == '>' || candidate == '<' || candidate == 'v' || candidate == '^';
	}

	Direction toDirection(char candidate) {
		switch (candidate) {
		case '>':
			return East;
		case '<':
			return West;
		case 'v':
			return South;
		case '^':
			return North;
		default:
			throw exception("unknown direction");
		}
	}

	char replaceDirection(Direction direction) {
		switch (direction) {
		case South:
		case North:
			return '|';
		case East:
		case West:
			return '-';
		default:
			throw exception("unknown direction");
		}
	}

	tuple<int, int> Part1(vector<string> lines) {
		char grid[6][13];
		vector<Cart> carts;
		auto s1 = lines.size();
		auto s2 = lines[0].size();
		for (int i = 0; i < lines.size(); i++) {
			for (int j = 0; j < lines[i].size(); j++) {
				auto candidate = lines[i][j];
				if (isCart(candidate)) {
					auto direction = toDirection(candidate);
					carts.push_back(Cart(i, j, direction));
					grid[i][j] = replaceDirection(direction);
				}
				else {
					grid[i][j] = candidate;
				}
			}
		}
		return make_tuple(0, 0);
	}
}
