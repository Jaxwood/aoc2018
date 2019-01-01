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

	bool Atlas::adjacent(Point p1, Point p2) {
		int x, y, x2, y2;
		tie(x, y) = p1;
		tie(x2, y2) = p2;
		if (x2 + 1 == x && y == y2) {
			return true;
		}
		if (x2 - 1 == x && y == y2) {
			return true;
		}
		if (x2 == x && y2 == y + 1) {
			return true;
		}
		if (x2 == x && y2 == y - 1) {
			return true;
		}
		return false;
	}

	// PLAYER

	Player::Player(Point position, bool isElf, int hitpoints) {
		this->hitpoints = hitpoints;
		this->location = position;
		this->elf = isElf;
	}

	bool Player::canReach(Player* opponent) const {
		if (this->elf == opponent->isElf()) {
			return false;
		}
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

	void Player::move(const Point destination) {
		this->location = destination;
	}

	bool Player::isElf() const {
		return this->elf;
	}

	int Player::health() const {
		return this->hitpoints;
	}

	bool Player::operator<(Player &other) const {
		return sortPoints(this->position(), other.position());
	}

	bool operator==(const Player &p1, const Player &p2) {
		return p1.position() == p2.position() && p1.health() == p2.health() && p1.isElf() == p2.isElf();
	}

	// PathFinder

	PathFinder::PathFinder(Atlas *atlas) {
		this->atlas = atlas;
	}

	vector<Point> PathFinder::targets(Point from) {
		auto type = this->atlas->at(from);
		return this->atlas->types(type == 'E' ? 'G' : 'E');
	}

	vector<Point> PathFinder::targetLocations(vector<Point> &targets)
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
		sort(begin(shortest), end(shortest), sortPoints);
		return shortest[0];
	}

	Point PathFinder::selectMove(Point from, Point to) {
		auto moves = this->atlas->neighbors(from);
		if (count_if(begin(moves), end(moves), [to](Point p) {return p == to; }) > 0) {
			return to;
		}
		auto costs = this->reachable(to, moves);
		auto shortest = this->shortestPath(costs);
		return this->selectByReadingOrder(shortest);
	}

	bool PathFinder::isAtTarget(Point from, vector<Point> &targets) {
		for (auto target : targets) {
			if (this->atlas->adjacent(from, target)) {
				return true;
			}
		}
		return false;
	}

	Point PathFinder::move(Point from) {
		auto targets = this->targets(from);
		if (!this->isAtTarget(from, targets)) {
			auto inrange = this->targetLocations(targets);
			auto reachable = this->reachable(from, inrange);
			if (reachable.size() > 0) {
				auto shortest = this->shortestPath(reachable);
				auto destination = this->selectByReadingOrder(shortest);
				auto move = this->selectMove(from, destination);
				this->atlas->swap(from, move);
				return move;
			}
		}
		return from;
	}

	bool sortPoints(Point p1, Point p2) {
		int x, y, x2, y2;
		tie(x, y) = p1;
		tie(x2, y2) = p2;
		if (y == y2) {
			return x < x2;
		}
		return y < y2;
	}

	// Game

	Game::Game(vector<Player> players) {
		this->players = players;
		this->turns = 0;
	}

	void Game::turn() {
		this->turns++;
	}

	bool Game::over() {
		auto elves = count_if(begin(this->players), end(this->players), [](Player p) {
			return p.isElf() && p.alive();
		});
		auto goblins = count_if(begin(this->players), end(this->players), [](Player p) {
			return !p.isElf() && p.alive();
		});
		return elves == 0 || goblins == 0;
	}

	Player* Game::attack(Player player) {
		if (player.alive() == false) {
			return nullptr;
		}
		vector<Player> opponents;
		for (auto opponent : this->players) {
			if (player.canReach(&opponent) && opponent.alive()) {
				opponents.push_back(opponent);
			}
		}

		if (opponents.size() == 0) {
			return nullptr;
		}

		// sort by hp then by reading order
		sort(begin(opponents), end(opponents), [](Player &p1, Player &p2) {
			if (p1.health() == p2.health()) {
				return sortPoints(p1.position(), p2.position());
			}
			return p1.health() < p2.health();
		});
		
		auto target = opponents[0];
		for (auto i = 0; i < this->players.size(); i++) {
			if (this->players[i].position() == target.position()) {
				player.attack(&this->players[i]);
				if (this->players[i].alive() == false) {
					return &this->players[i];
				}
				break;
			}
		}
		return nullptr;
	}

	vector<Player> Game::participants() {
		return this->players;
	}

	void Game::order() {
		sort(begin(this->players), end(this->players));
	}

	Player Game::move(Player player, Point to) {
		for (auto i = 0; i < this->players.size(); i++) {
			if (this->players[i].alive() == false) {
				continue;
			}
			if (this->players[i].position() == player.position()) {
				this->players[i].move(to);
				return this->players[i];
			}
		}
	}

	int Game::score() {
		int sum = 0;
		for (auto player : this->players) {
			if (player.alive()) {
				sum += player.health();
			}
		}

		return this->turns * sum;
	}
	bool Game::isAlive(Player player) {
		for (auto &candidate : this->players) {
			if (player.position() == candidate.position()) {
				return candidate.alive();
			}
		}

		return false;
	}

	void Game::sync() {
		vector<Player> survivors;
		copy_if(begin(this->players), end(this->players), back_inserter(survivors), [](Player player) {
			return player.alive();
		});
		this->players = survivors;
	}

	int Part1(vector<string> lines) {
		auto atlas = Atlas();
		atlas.initialize(lines);
		auto pathfinder = PathFinder(&atlas);
		vector<Player> players;
		auto elves = atlas.types('E');
		auto goblins = atlas.types('G');
		transform(begin(elves), end(elves), back_inserter(players), [](Point p) {
			return Player(p, true, 200);
		});
		transform(begin(goblins), end(goblins), back_inserter(players), [](Point p) {
			return Player(p, false, 200);
		});
		auto game = Game(players);
		auto end = false;
		while(!game.over()) {
			game.order();
			for (auto &player : game.participants()) {
				if (game.isAlive(player)) {
					if (pathfinder.targets(player.position()).size() == 0) {
						end = true;
						break;
					}
					auto to = pathfinder.move(player.position());
					auto movedPlayer = game.move(player, to);
					auto attackedPlayer = game.attack(movedPlayer);
					if (attackedPlayer != nullptr) {
						atlas.clear(attackedPlayer->position());
					}
				}
			}
			if (!end) {
				game.turn();
			}
			game.sync();
			// verify sync
			for (auto &p : game.participants()) {
				if (p.alive() == false) {
					continue;
				}
				auto c = atlas.at(p.position());
				if (p.isElf() && c != 'E') {
					throw exception("Elf out of sync");
				}
				if (!p.isElf() && c != 'G') {
					throw exception("Goblins out of sync");
				}
			}
		}

		return game.score();
	}
}
