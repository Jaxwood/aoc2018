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

	void Atlas::swap(const Point p1, const Point p2) {
		int x1, y1, x2, y2;
		tie(x1, y1) = p1;
		tie(x2, y2) = p2;
		auto from = this->grid[y1][x1];
		auto to = this->grid[y2][x2];
		this->grid[y1][x1] = to;
		this->grid[y2][x2] = from;
	}

	void Atlas::clear(const Point point) {
		int x, y;
		tie(x, y) = point;
		this->grid[y][x] = OPEN;
	}

	vector<Point> Atlas::neighbors(const Point point) const {
		int x, y;
		tie(x, y) = point;
		vector<Point> neighborhood;
		if (this->grid[y + 1][x] == OPEN) {
			neighborhood.push_back(make_tuple(x, y+1));
		}
		if (this->grid[y - 1][x] == OPEN) {
			neighborhood.push_back(make_tuple(x, y-1));
		}
		if (this->grid[y][x + 1] == OPEN) {
			neighborhood.push_back(make_tuple(x + 1, y));
		}
		if (this->grid[y][x - 1] == OPEN) {
			neighborhood.push_back(make_tuple(x - 1, y));
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

	char Atlas::at(Point point) const {
		int x, y;
		tie(x, y) = point;
		return this->grid[y][x];
	}

	// PLAYER

	Player::Player(Point position, int hitpoints) {
		this->hitpoints = hitpoints;
		this->location = position;
	}

	bool Player::canReach(Player* opponent) const {
		int x, y;
		tie(x, y) = this->position();
		if (make_tuple(x + 1, y) == opponent->position()) {
			return true;
		}
		if (make_tuple(x - 1, y) == opponent->position()) {
			return true;
		}
		if (make_tuple(x, y + 1) == opponent->position()) {
			return true;
		}
		if (make_tuple(x, y - 1) == opponent->position()) {
			return true;
		}
		return false;
	}

	void Player::attack(Player *opponent) const {
		if (canReach(opponent)) {
			opponent->takehit();
		}
	}

	void Player::takehit() {
		this->hitpoints -= 3;
	}

	Point Player::position() const {
		return this->location;
	}

	bool Player::alive() const {
		return this->hitpoints > 0;
	}

	bool Player::operator<(Player &other) const {
		int x, y, x2, y2;
		tie(x, y) = this->position();
		tie(x2, y2) = other.position();
		if (y == y2) {
			return x < x2;
		}
		return y < y2;
	}

	bool operator==(const Player &p1, const Player &p2) {
		return p1.position() == p2.position();
	}

	// PathFinder

	PathFinder::PathFinder(Atlas *atlas) {
		this->atlas = atlas;
	}

	vector<Point> PathFinder::targets(Point from) {
		auto type = this->atlas->at(from);
		return this->atlas->types(type == 'E' ? 'G' : 'E');
	}

	vector<Point> PathFinder::targetsInRange(vector<Point> &targets)
	{
		vector<Point> locations;
		for (auto &target : targets) {
			for (auto &neighbor : this->atlas->neighbors(target)) {
				locations.push_back(neighbor);
			}
		}
		return locations;
	}

	map<Point, int> PathFinder::reachable(Point from, vector<Point> &targets)
	{
		map<Point, int> canBeReached;
		for (auto &target : targets) {
			queue<Point> queue;
			vector<Point> visited = { from };
			map<Point, Point> parents;
			queue.push(from);
			while (!queue.empty()) {
				auto next = queue.front();
				queue.pop();
				if (next == target) {
					canBeReached[target] = nearest(from, target, parents);
					break;
				}
				else {
					visited.push_back(next);
					for (auto &neighbor : this->atlas->neighbors(next)) {
						if (count_if(begin(visited), end(visited), [neighbor](Point p) { return p == neighbor; }) == 0) {
							queue.push(neighbor);
							parents[neighbor] = next;
						}
					}
				}
			}
		}
		return canBeReached;
	}

	int PathFinder::nearest(Point from, Point target, map<Point, Point> parents) {
		int cnt = 0;
		while (true) {
			auto p = parents[target];
			if (p == from) {
				return cnt;
			}
			cnt++;
			target = p;
		}
	}

	vector<Point> PathFinder::shortestPath(map<Point, int> paths) {
		int min = INT_MAX;
		for(auto path : paths) {
			int score = path.second;
			if (score < min) {
				min = score;
			}
		}
		vector<Point> shortest;
		for(auto path : paths) {
			if (path.second == min) {
				shortest.push_back(path.first);
			}
		}
		return shortest;
	}

	Point PathFinder::selectByReadingOrder(vector<Point> shortest) {
		if (shortest.size() == 0) {
			throw exception("no path availible");
		}
		sort(begin(shortest), end(shortest), [](Point p1, Point p2) {
			int x, y, x2, y2;
			tie(x, y) = p1;
			tie(x2, y2) = p2;
			if (y == y2) {
				return x < x2;
			}
			return y < y2;
		});
		return shortest[0];
	}

	Point PathFinder::selectMove(Point from, Point to) {
		auto moves = this->atlas->neighbors(from);
		auto costs = this->reachable(to, moves);
		auto shortest = this->shortestPath(costs);
		return this->selectByReadingOrder(shortest);
	}

	void PathFinder::move(Point from) {
		auto targets = this->targets(from);
		auto inrange = this->targetsInRange(targets);
		auto reachable = this->reachable(from, inrange);
		auto shortest = this->shortestPath(reachable);
		auto destination = this->selectByReadingOrder(shortest);
		auto move = this->selectMove(from, destination);
		this->atlas->swap(from, move);
	}

	int Part1(vector<string> lines) {
		return 0;
	}
}
