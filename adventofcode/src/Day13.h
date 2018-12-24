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

	class Network {
	private:
		vector<string> lines;
		vector<Cart> carts;
		char grid[6][13];

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

	public:
		Network(vector<string> lines) {
			this->lines = lines;
		}

		void setup() {
			vector<Cart> carts;
			for (int i = 0; i < lines.size(); i++) {
				for (int j = 0; j < lines[i].size(); j++) {
					auto candidate = lines[i][j];
					if (this->isCart(candidate)) {
						auto direction = this->toDirection(candidate);
						carts.push_back(Cart(i, j, direction));
						this->grid[i][j] = this->replaceDirection(direction);
					}
					else {
						this->grid[i][j] = candidate;
					}
				}
			}
			this->carts = carts;
		}

		bool tick() {
			return false;
		}

		tuple<int, int> collesion() {
			return make_tuple(0, 0);
		}
	};

	tuple<int, int> Part1(vector<string> lines);

}
