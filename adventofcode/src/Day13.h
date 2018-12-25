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

		void drive() {
			switch (this->direction) {
			case North:
					this->y -= 1;
					break;
			case South:
					this->y += 1;
					break;
			case East:
					this->x += 1;
					break;
			case West:
					this->x -= 1;
					break;
			}
		}
	public:
		Cart(int x, int y, char pathway, Direction direction) {
			this->x = x;
			this->y = y;
			this->pathway = pathway;
			this->direction = direction;
			this->decision = Left;
		}

		tuple<int, int> position() const {
			return make_tuple(this->x, this->y);
		}

		tuple<int, int> move() {
			switch (this->pathway) {
			case '|':
			case '-':
				break;
			case '+':
				switch (this->decision) {
				case Left:
					this->decision = Straight;
					switch (this->direction) {
					case East:
						this->direction = North;
						break;
					case West:
						this->direction = South;
						break;
					case North:
						this->direction = West;
						break;
					case South:
						this->direction = East;
						break;
					}
					break;
				case Straight:
					this->decision = Right;
					break;
				case Right:
					this->decision = Left;
					switch (this->direction) {
					case East:
						this->direction = South;
						break;
					case West:
						this->direction = North;
						break;
					case North:
						this->direction = East;
						break;
					case South:
						this->direction = West;
						break;
					}
					break;
				}
				break;
			case '/':
				switch (this->direction) {
				case East:
					this->direction = North;
					break;
				case West:
					this->direction = South;
					break;
				case North:
					this->direction = East;
					break;
				case South:
					this->direction = West;
					break;
				}
				break;
			case '\\':
				switch (this->direction) {
				case East:
					this->direction = South;
					break;
				case West:
					this->direction = North;
					break;
				case North:
					this->direction = West;
					break;
				case South:
					this->direction = East;
					break;
				}
				break;
			default:
				throw exception("unknown pathway: " + this->pathway);
			}
			this->drive();
			return make_tuple(this->x, this->y);
		}

		void setPath(char pathway) {
			this->pathway = pathway;
		}

		bool operator<(Cart &other) {
			if (this->y == other.y) {
				return this->x < other.x;
			}
			return this->y < other.y;
		}

		bool operator==(Cart &other) {
			return this->position() == other.position();
		}
	};

	bool operator==(const Cart &c1, const Cart &c2);

	class Network {
	private:
		vector<string> lines;
		vector<Cart> carts;
		char grid[200][200];
		tuple<int, int> collisionCoord;

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

		bool isCollision(Cart &cart) {
			if (count_if(begin(this->carts), end(this->carts), [&cart](Cart &other) { return cart.position() == other.position();  }) > 1) {
				this->collisionCoord = cart.position();
				return true;
			}
			return false;
		}

		void removeCarts() {
			vector<Cart> nonCrashedCarts;
			for (auto &cart : this->carts) {
				if (!isCollision(cart)) {
					nonCrashedCarts.push_back(cart);
				}
			}
			this->carts = nonCrashedCarts;
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
						this->grid[j][i] = pathway;
					}
					else {
						this->grid[j][i] = candidate;
					}
				}
			}
			this->carts = carts;
			sort(begin(this->carts), end(this->carts));
		}

		bool tick() {
			int x, y = 0;
			for (auto &cart : this->carts) {
				tie(x,y) = cart.move();
				cart.setPath(grid[x][y]);
				if (isCollision(cart)) {
					return false;
				}
			}
			sort(begin(this->carts), end(this->carts));
			return true;
		}

		bool crashes() {
			int x, y = 0;
			for (auto &cart : this->carts) {
				tie(x,y) = cart.move();
				cart.setPath(grid[x][y]);
			}
			this->removeCarts();
			sort(begin(this->carts), end(this->carts));
			return this->carts.size() != 1;
		}

		tuple<int, int> lastCart() {
			return this->carts[0].position();
		}

		tuple<int, int> collesion() {
			return this->collisionCoord;
		}
	};

	tuple<int, int> Part1(vector<string> lines);

	tuple<int, int> Part2(vector<string> lines);

}
