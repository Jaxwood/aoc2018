#include "Day15.h"

using namespace std;

namespace Day15 {

	bool Atlas::equal(const Atlas &other) const{
		for (auto i = 0; i < this->size; i++) {
			for (auto j = 0; j < this->size; j++) {
				if (this->grid[i][j] != other.grid[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator==(const Atlas &a1, const Atlas &a2) {
		return a1.equal(a2);
	}

	void Atlas::swap(Point p1, Point p2) {
		int x1, y1, x2, y2;
		tie(x1, y1) = p1;
		tie(x2, y2) = p2;
		auto from = this->grid[y1][x1];
		auto to = this->grid[y2][x2];
		this->grid[y1][x1] = to;
		this->grid[y2][x2] = from;
	}

	void Atlas::clear(Point point) {
		int x, y;
		tie(x, y) = point;
		this->grid[y][x] = OPEN;
	}

	vector<Point> Atlas::neighbors(Point point) const {
		int x, y;
		tie(x, y) = point;
		vector<Point> neighborhood;
		if (this->grid[y + 1][x] == OPEN) {
			neighborhood.push_back(make_tuple(x + 1, y));
		}
		if (this->grid[y - 1][x] == OPEN) {
			neighborhood.push_back(make_tuple(x + 1, y));
		}
		if (this->grid[y][x + 1] == OPEN) {
			neighborhood.push_back(make_tuple(x + 1, y));
		}
		if (this->grid[y][x - 1] == OPEN) {
			neighborhood.push_back(make_tuple(x + 1, y));
		}
		return neighborhood;
	}

	vector<Point> Atlas::types(const char c) const {
		auto matches = vector<Point>();
		for (auto y = 0; y < size; y++) {
			for (auto x = 0; x < size; x++) {
				if (this->grid[y][x] == c) {
					matches.push_back(make_tuple(x, y));
				}
			}
		}
		return matches;
	}

	void Atlas::initialize(vector<string> raw) {
		for (auto y = 0; y < raw.size(); y++) {
			for (auto x = 0; x < raw[y].size(); x++) {
				this->grid[y][x] = raw[y][x];
			}
		}
	}

	int Part1(vector<string> lines) {
		return 0;
	}
}
