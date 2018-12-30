#include "Day15.h"

using namespace std;

namespace Day15 {

	typedef tuple<int, int> Point;

	class Player {
		int x, y;
		char c;
		int hitpoints;
	public:
		Player(int x, int y, char c) {
			this->x = x;
			this->y = y;
			this->c = c;
			this->hitpoints = 200;
		}

		bool isElf() const {
			return this->c == 'E';
		}

		Point position() const {
			return make_tuple(this->x, this->y);
		}

		void setPosition(int x, int y) {
			this->x = x;
			this->y = y;
		}

		void takeDamage() {
			this->hitpoints -= 3;
		}

		bool alive() {
			return this->hitpoints > 0;
		}

		bool operator<(Player &other) {
			if (this->y == other.y) {
				return this->x < other.x;
			}

			return this->y < other.y;
		}

		bool operator==(Player &other) {
			return this->position() == other.position();
		}
	};

	const int size = 10;
	vector<Player> players;
	char grid[size][size];
	map<Point, vector<Point>> atlas;
	char OPEN = '.';

	void updateGrid(int x, int y, char c) {
		grid[y][x] = c;
	}

	char at(int x, int y) {
		return grid[y][x];
	}

	void setup(std::vector<std::string> &lines)
	{
		for (auto y = 0; y < lines.size(); y++) {
			for (auto x = 0; x < lines[y].size(); x++) {
				updateGrid(x, y, lines[y][x]);
				if (lines[y][x] == 'E' || lines[y][x] == 'G') {
					players.push_back(Player(x,y,lines[y][x]));
				}
			}
		}
	}

	vector<Point> neighbors(int x, int y) {
		vector<tuple<int, int>> result;
		if (at(x + 1,y) == OPEN) { result.push_back(make_tuple(x + 1, y)); }
		if (at(x - 1,y) == OPEN) { result.push_back(make_tuple(x - 1, y)); }
		if (at(x, y + 1) == OPEN) { result.push_back(make_tuple(x, y + 1)); }
		if (at(x, y - 1) == OPEN) { result.push_back(make_tuple(x, y - 1)); }

		return result;
	}

	vector<Point> neighbors(Point position) {
		int x, y;
		tie(x, y) = position;
		return neighbors(x, y);
	}

	map<Point, vector<Point>> openFields() {
		map<Point, vector<Point>> fields;
		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				if (at(x,y) == OPEN) {
					fields[make_tuple(x, y)] = neighbors(x, y);
				}
			}
		}
		return fields;
	}

	vector<Player> findTargets(Player player) {
		vector<Player> targets;
		copy_if(begin(players), end(players), back_inserter(targets), [player](Player p) {
			return player.isElf() != p.isElf();
		});
		return targets;
	}

	Point readingOrder(vector<Point> destinations) {
		sort(begin(destinations), end(destinations), [](Point p1, Point p2) {
			int x1, y1, x2, y2;
			tie(x1, y1) = p1;
			tie(x2, y2) = p2;
			if (y1 == y2) {
				return x2 < x1;
			}
			return y1 < y2;
		});
		return destinations[0];
	}

	bool canAttack(Point player, Point target) {
		int x, y, x2, y2;
		tie(x, y) = player;
		tie(x2, y2) = target;
		if (x + 1 == x2 && y == y2) {
			return true;
		}
		if (x - 1 == x2 && y == y2) {
			return true;
		}
		if (x == x2 && y + 1 == y2) {
			return true;
		}
		if (x == x2 && y - 1 == y2) {
			return true;
		}
		return false;
	}

	bool reachable(Point from, Point to) {
		atlas = openFields();
		vector<Point> visited = { from }; queue<Point> queue;
		if (canAttack(from, to)) {
			return true;
		}

		auto targets = neighbors(to);

		for (auto &p : neighbors(from)) {
			queue.push(p);
		}
		while (!queue.empty()) {
			auto point = queue.front();
			queue.pop();
			if (count_if(begin(targets), end(targets), [point](Point target) { return point == target; }) > 0) {
				return true;
			}
			else {
				visited.push_back(point);
				for (auto &n : atlas[point]) {
					if (count(begin(visited), end(visited), n) == 0) {
						queue.push(n);
					}
				}
			}
		}
		return false;
	}

	bool isWithinRange(Player player, vector<Player> targets) {
		for (auto target : targets) {
			if (canAttack(player.position(), target.position()) && target.alive()) {
				return true;
			}
		}
		return false;
	}

	Point closest(Player player, vector<Player> destinations) {
		map<Point, Point> parents;
		map<Point, int> costs;
		map<Point, map<Point, int>> destinationCost;
		atlas = openFields();
		auto from = player.position();
		for (auto destination : destinations) {
			auto to = destination.position();
			vector<Point> visited = { to }; queue<Point> visiting;

			atlas[from] = neighbors(from);
			for_each(begin(atlas[from]), end(atlas[from]), [from](Point p) {
				atlas[p].push_back(from);
			});
			atlas[to] = neighbors(to);
			for_each(begin(atlas[to]), end(atlas[to]), [to](Point p) {
				atlas[p].push_back(to);
			});

			for (auto &neighbor : atlas[to]) {
				parents[neighbor] = to;
				costs[neighbor] = 1;
				visiting.push(neighbor);
			}
			while (!visiting.empty()) {
				auto location = visiting.front();
				visiting.pop();
				visited.push_back(location);
				for (auto &neighbor : atlas[location]) {
					if (count(begin(visited), end(visited), neighbor) == 0) {
						parents[neighbor] = location;
						costs[neighbor] = 1 + costs[location];
						visiting.push(neighbor);
					}
				}
			}
			destinationCost[destination.position()] = costs;
		}

		int lowestCost = INT_MAX;
		for (auto &destination : destinations) {
			auto costs = destinationCost[destination.position()];
			for (auto &neighbor : neighbors(player.position())) {
				auto cost = costs[neighbor];
				if (cost < lowestCost) {
					lowestCost = cost;
				}
			}
		}
		vector<Point> lowCostPlayers;
		for (auto &destination : destinations) {
			auto costs = destinationCost[destination.position()];
			for (auto &neighbor : neighbors(player.position())) {
				auto cost = costs[neighbor];
				if (cost == lowestCost) {
					lowCostPlayers.push_back(neighbor);
				}
			}
		}
    
		return readingOrder(lowCostPlayers);
	}

	void attack(Player player, vector<Player> targets) {
		vector<Player> attackable;
		for (int i = 0; i < targets.size(); i++) {
			if (player.position() == targets[i].position()) {
				continue;
			}
			if (canAttack(player.position(), targets[i].position())) {
				attackable.push_back(players[i]);
			}
		}
		if (attackable.size() == 0) return;

		sort(begin(attackable), end(attackable));
		auto target = attackable[0].position();
		for (auto i = 0; i < players.size(); i++) {
			if (players[i].position() == target) {
				players[i].takeDamage();
				// update grid
				int x, y;
				tie(x, y) = players[i].position();
				updateGrid(x, y, OPEN);
			}
		}
	}

	bool game() {
		return count_if(begin(players), end(players), [](Player player){
			return player.isElf() && player.alive();
		}) > 0;
	}

	int Part1(vector<string> lines) {
		setup(lines);
		while(game()) {
			sort(begin(players), end(players));
			for (int i = 0; i < players.size(); i++) {
				vector<Player> inrange;
				auto player = players[i];
				if (!player.alive()) {
					continue;
				}
				auto targets = findTargets(player);
				copy_if(begin(targets), end(targets), back_inserter(inrange), [player](Player t) {
					return reachable(player.position(), t.position());
				});
				if (inrange.size() == 0) {
					continue;
				}

				if (!isWithinRange(player, inrange)) {
					int x, y, x2, y2;
					auto pos = closest(player, inrange);
					if (pos == player.position()) throw exception("invalid");
					tie(x, y) = pos;
					updateGrid(x, y, player.isElf() ? 'E' : 'G');
					tie(x2, y2) = player.position();
					updateGrid(x2, y2, OPEN);
					players[i].setPosition(x, y);
				}
				// attack
				attack(player, inrange);
			}
			// remove dead players
			vector<Player> alive;
			copy_if(begin(players), end(players), back_inserter(alive), [](Player player) {
				return player.alive();
			});
			players = alive;
		}
		return 0;
	}
}
