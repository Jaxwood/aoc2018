#pragma once

#include <tuple>
#include <vector>

using namespace std;

namespace Day13 {

	class Cart {
		int x = 0;
		int y = 0;
	public:
		Cart(int x, int y) {
			this->x = x;
			this->y = y;
		}
	};

	class Grid {
	private:
		char grid[5][12];
		vector<Cart> carts;

		bool isCart(char candidate) {
			return candidate == '>' || candidate == '<' || candidate == 'v' || candidate == '^';
		}

	public:
		Grid(vector<string> lines) {
			for (int i = 0; i < lines.size(); i++) {
				for (int j = 0; j < lines[i].size(); j++) {
					auto candidate = lines[i][j];
					grid[i][j] = candidate;
					if (isCart(candidate)) {
						carts.push_back(Cart(i, j));
					}
				}
			}
		}

		void tick(vector<Cart> carts) {
			for (auto &cart : carts) {
			}
		}
	};
	tuple<int, int> Part1(vector<string> lines);
}
