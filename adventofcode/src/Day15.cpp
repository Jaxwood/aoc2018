#include "Day15.h"

using namespace std;

namespace Day15 {

	Player::Player(int x, int y, char type) {
		this->x = x;
		this->y = y;
		this->hitpoints = 200;
		this->playerType = type == 'E' ? Elf : Goblin;
	}

	void Player::takeDamage() {
		this->hitpoints -= 3;
	}

	tuple<int, int> Player::position() const {
		return make_tuple(this->x, this->y);
	}

	void Player::move(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool Player::dead() {
		return this->hitpoints <= 0;
	}

	bool Player::operator<(Player &other) {
		if (this->y == other.y) {
			return this->x < other.x;
		}
		return this->y < other.y;
	}
	BattleField::BattleField() {
	}

	void BattleField::addCoord(int x, int y, char c) {
		if (c == 'E' || c == 'G') {
			this->players.push_back(Player(x, y, c));
		}
		this->grid[x][y] = c;
	}

	vector<Player> BattleField::targets(Player player) {
		vector<Player> opponents;
		copy_if(begin(this->players), end(this->players), back_inserter(opponents), [player](Player candidate) {
			if (candidate.position() != player.position() && candidate.type() != player.type()) {
				return true;
			}
			return false;
		});

		return opponents;
	}

	vector<Player> BattleField::inRange(vector<Player> candidates) {
		auto grid = this->grid;
		vector<Player> opponents;
		copy_if(begin(candidates), end(candidates), back_inserter(opponents), [grid](Player candidate) {
			int x, y;
			tie(x, y) = candidate.position();
			return grid[x + 1][y] == '.' || grid[x - 1][y] == '.' || grid[x][y + 1] == '.' || grid[x][y - 1] == '.';
		});

		return opponents;
	}

	vector<tuple<int, int>> BattleField::neighbors(int x, int y) {
		vector<tuple<int, int>> candidates;
		if (this->grid[x+1][y] == '.') {
			candidates.push_back(make_tuple(x+1, y));
		}
		if (this->grid[x-1][y] == '.') {
			candidates.push_back(make_tuple(x-1, y));
		}
		if (this->grid[x][y+1] == '.') {
			candidates.push_back(make_tuple(x, y+1));
		}
		if (this->grid[x][y - 1] == '.') {
			candidates.push_back(make_tuple(x, y-1));
		}
		return candidates;
	}

	bool BattleField::canReach(tuple<int, int> from, tuple<int, int> to, map<tuple<int, int>, vector<tuple<int, int>>> squares) {
		vector<tuple<int, int>> checked = { from };
		queue<tuple<int, int>> candidates;
		if (from == to) {
			return true;
		}
		for (auto &c : squares[from]) {
			candidates.push(c);
		}
		while (candidates.size() > 0) {
			auto c = candidates.front();
			candidates.pop();
			if (c == to) {
				return true;
			}
			else {
				checked.push_back(c);
				for (auto &candidate : squares[c]) {
					if (count(begin(checked), end(checked), candidate) == 0) {
						candidates.push(candidate);
					}
				}
			}
		}
		return false;
	}

	vector<Player> BattleField::reachable(Player player, vector<Player> candidates) {
		vector<Player> result;
		int x, y;
		tie(x, y) = player.position();
		this->grid[x][y] = '.';
		for (auto &c : candidates) {
			tie(x, y) = c.position();
			this->grid[x][y] = '.';
		}
		auto openSquares = map<tuple<int, int>, vector<tuple<int, int>>>();
		for (int y = 0; y < 7; y++) {
			for (int x = 0; x < 7; x++) {
				if (this->grid[x][y] == '.') {
					openSquares[make_tuple(x, y)] = this->neighbors(x, y);
				}
			}
		}
		this->grid[x][y] = player.type() == Elf ? 'E' : 'G';
		for (auto &c : candidates) {
			tie(x, y) = c.position();
			this->grid[x][y] = c.type() == Elf ? 'E' : 'G';
		}
		for (auto &candidate : candidates) {
			if (this->canReach(player.position(), candidate.position(), openSquares)) {
				result.push_back(candidate);
			}
		}
		return result;
	}

	Player BattleField::nearest(Player player, vector<Player> players) {
		map<int, vector<Player>> result;
		int x1, y1, x2, y2;
		tie(x1,y1) = player.position();
		for (auto &p : players) {
			tie(x2, y2) = p.position();
			auto dist = abs(x1 - x2) + abs(y1 - y2);
			result[dist].push_back(p);
		}

		auto candidate = *min_element(begin(result), end(result), [](std::pair<int, vector<Player>> p1, std::pair<int, vector<Player>> p2) {
			return p1.first < p2.first;
		});

		if (candidate.second.size() > 1) {
			auto candidates = candidate.second;
			sort(begin(candidates), end(candidates));
			return candidates[0];
		}
		else {
			return candidate.second[0];
		}
	}

	void BattleField::chooseMove(Player from, Player to) {
		int x1, y1, x2, y2;
		tie(x1, y1) = from.position();
		tie(x2, y2) = to.position();

		if (y1 == y2) {
			// right
			if (x1 < x2) {

			}
			else {
				// left
				
			}
		}
		if (y1 < y2) {
			// down
			if(this->grid[x1][y1+1] == '.')
		}
		else {
			// up
		}
	}

	void BattleField::move(Player player) {
		auto opponents = this->targets(player);
		opponents = this->inRange(opponents);
		opponents = this->reachable(player, opponents);
		auto opponent = this->nearest(player, opponents);
		this->chooseMove(player, opponent);
	}

	Game::Game() {
		this->turnCount = 0;
	}

	void Game::removeDeadPlayers() {
		 vector<Player> alive;
		 copy_if(begin(this->players), end(this->players), back_inserter(alive), [](Player player) { return !player.dead(); });
		 this->players = alive;
	}

	void Game::setup(vector<string> lines) {
		for (int y = 0; y < lines.size(); y++) {
			for (int x = 0; x < lines[y].size(); x++) {
				auto candidate = lines[y][x];
				if (candidate == 'G' || candidate == 'E') {
					this->players.push_back(Player(x,y, candidate));
				}
				this->battleField.addCoord(x, y, candidate);
			}
		}
	}

	void Game::turn() {
		// sort by reading order
		sort(begin(this->players), end(this->players));
		// each player takes turn
		for (auto &player : this->players) {
			// move
			this->battleField.move(player);
			// attack
			// update
		}
		// end turn
		this->removeDeadPlayers();
		this->turnCount++;
	}

	bool Game::over() {
		auto elves = count_if(begin(this->players), end(this->players), [](Player player) { return player.type() == Elf; });
		auto goblins = count_if(begin(this->players), end(this->players), [](Player player) { return player.type() == Goblin; });
		return elves == 0 || goblins == 0;
	}

	bool operator==(const Player &p1, const Player &p2) {
		return p1.position() == p2.position();
	}

	int Part1(vector<string> lines) {
		auto game = Game();
		game.setup(lines);
		while (!game.over()) {
			game.turn();
		}
		return game.turns();
	}
}
