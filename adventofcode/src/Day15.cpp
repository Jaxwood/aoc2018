#include "Day15.h"

using namespace std;

namespace Day15 {
	
	Player::Player(int x, int y, char type) {
		this->x = x;
		this->y = y;
		this->hitpoints = 200;
		this->playerType = type == 'E' ? Elf : Goblin;
	}

	bool Player::inRange(Player &player) {
		return this->distance(player) == 1;
	}

	bool Player::takeDamage(Player &player) {
		if (this->inRange(player)) {
			this->hitpoints -= 3;
		}
		return this->hitpoints <= 0;
	}

	void Player::move(Player &player) {
		if (this->inRange(player)) {
			return;
		}
		if (this->x > player.x) {
			this->x -= 1;
		}
		else if (this->x < player.x) {
			this->x += 1;
		}
		else if (this->y > player.y) {
			this->y -= 1;
		}
		else {
			this->y += 1;
		}
	}

	tuple<int,int> Player::position() const {
		return make_tuple(this->x, this->y);
	}

	int Player::distance(Player &player) {
		return abs(this->x - player.x) + abs(this->y - player.y);
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

	Game::Game(vector<string> lines) {
		this->lines = lines;
		this->turnCount = 0;
	}

	void Game::setup() {
		char grid[7][7];
		for (int y = 0; y < lines.size(); y++) {
			for (int x = 0; x < lines[y].size(); x++) {
				auto candidate = lines[y][x];
				if (candidate == 'G' || candidate == 'E') {
					this->players.push_back(Player(x,y, candidate));
					this->grid[x][y] = '.';
				}
				else {
					this->grid[x][y] = candidate;
				}
			}
		}
	}

	int Game::opponentFor(Player &player) {
		int shortestDistance = INT_MAX;
		int index = -1;
		for (int i = 0; i < this->players.size(); i++) {
			auto opponent = this->players[i];
			if (opponent.type() == player.type()) {
				continue;
			}
			if (opponent.dead()) {
				continue;
			}
			auto range = player.distance(opponent);
			if (range < shortestDistance) {
				shortestDistance = range;
				index = i;
			}
		}
		return index;
	}

	void Game::removeDeadPlayers() {
		 vector<Player> survivors;
		 copy_if(begin(this->players), end(this->players), back_inserter(survivors), [](Player player) { return !player.dead(); });
		 this->players = survivors;
	}

	void Game::turn() {
		// sort by reading order
		sort(begin(this->players), end(this->players));
		// each player takes turn
		for (auto &player : this->players) {
			// find opponent
			auto opponent = this->opponentFor(player);
			if (opponent == -1) {
				continue;
			}
			// move towards opponent
			player.move(this->players[opponent]);
			// attack opponent
			this->players[opponent].takeDamage(player);
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
		auto game = Game(lines);
		game.setup();
		while (!game.over()) {
			game.turn();
		}
		return game.turns();
	}
}
