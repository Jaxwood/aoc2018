#pragma once

#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

namespace Day13 {

	enum Direction {
		North,
		South,
		East,
		West
	};

	enum Decision {
		Left,
		Straight,
		Right
	};

	class Cart {
	private:
		int x, y;
		char pathway;
		Direction direction;
		Decision decision;
	public:
		Cart(int x, int y, char pathway, Direction direction) {
			this->x = x;
			this->y = y;
			this->pathway = pathway;
			this->direction = direction;
			this->decision = Left;
		}

		tuple<int, int> position() {
			return make_tuple(this->x, this->y);
		}

		tuple<int, int> move() {
			switch (this->pathway) {
			case '|':
				switch (this->direction) {
				case North:
					this->y -= 1;
					break;
				case South:
					this->y += 1;
					break;
				}
				break;
			case '-':
				switch (this->direction) {
				case East:
					this->x += 1;
					break;
				case West:
					this->x -= 1;
					break;
				}
				break;
			case '+':
				switch (this->decision) {
				case Left:
					this->decision = Straight;
					switch (this->direction) {
					case East:
						this->direction = North;
						this->y -= 1;
						break;
					case West:
						this->direction = South;
						this->y += 1;
						break;
					case North:
						this->direction = West;
						this->x -= 1;
						break;
					case South:
						this->direction = East;
						this->x += 1;
						break;
					}
					break;
				case Straight:
					this->decision = Right;
					switch (this->direction) {
					case East:
						this->x += 1;
						break;
					case West:
						this->x -= 1;
						break;
					case North:
						this->y -= 1;
						break;
					case South:
						this->y += 1;
						break;
					}
					break;
				case Right:
					this->decision = Left;
					switch (this->direction) {
					case East:
						this->direction = South;
						this->y += 1;
						break;
					case West:
						this->direction = North;
						this->y -= 1;
						break;
					case North:
						this->direction = East;
						this->x += 1;
						break;
					case South:
						this->direction = West;
						this->x -= 1;
						break;
					}
					break;
				}
			case '/':
				switch (this->direction) {
				case East:
					this->direction = North;
					this->y -= 1;
					break;
				case West:
					this->direction = South;
					this->y += 1;
					break;
				case North:
					this->direction = East;
					this->x += 1;
					break;
				case South:
					this->direction = West;
					this->x -= 1;
					break;
				}
				break;
			case '\\':
				switch (this->direction) {
				case East:
					this->direction = South;
					this->y += 1;
					break;
				case West:
					this->direction = North;
					this->y -= 1;
					break;
				case North:
					this->direction = West;
					this->x -= 1;
					break;
				case South:
					this->direction = East;
					this->x += 1;
					break;
				}
				break;
			default:
				throw exception("unknown pathway: " + this->pathway);
			}
			return make_tuple(this->x, this->y);
		}

		void setPath(char pathway) {
			this->pathway = pathway;
		}

		bool operator<(Cart &cart) {
			if (this->x < cart.x) {
				return true;
			}
			if (this->y < cart.y) {
				return true;
			}
			return false;
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

		char replaceCart(Direction direction) {
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

		bool collide() {
			return false;
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
						char pathway = this->replaceCart(direction);
						carts.push_back(Cart(j, i, pathway, direction));
						this->grid[i][j] = pathway;
					}
					else {
						this->grid[i][j] = candidate;
					}
				}
			}
			this->carts = carts;
		}

		bool tick() {
			int x, y = 0;
			for (auto &cart : this->carts) {
				tie(x,y) = cart.move();
				cart.setPath(grid[y][x]);
			}
			sort(begin(this->carts), end(this->carts));
			return collide();
		}

		tuple<int, int> collesion() {
			return make_tuple(0, 0);
		}
	};

	tuple<int, int> Part1(vector<string> lines);

}
