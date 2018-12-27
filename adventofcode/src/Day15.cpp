#include "Day15.h"

using namespace std;

namespace Day15 {
	
	Player::Player(int x, int y, char type) {
		this->x = x;
		this->y = y;
		this->hitpoints = 200;
		this->playerType = type == 'E' ? Elf : Goblin;
	}

	bool Player::inRange(const Player *player) {
		return abs(this->x - (*player).x) + abs(this->y - (*player).y) == 2;
	}

	bool Player::attack(Player &player) {
		if (player.inRange(this)) {
			return player.takeDamage();
		}
		return false;
	}

	bool Player::takeDamage() {
		this->hitpoints -= 3;
		return this->hitpoints <= 0;
	}

	void Player::move(Player player) {
		// TODO
	}

	tuple<int,int> Player::position() const {
		return make_tuple(this->x, this->y);
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


	Player& Game::opponentFor(Player &player) {
		// TODO
		return this->players[1];
	}

	void Game::remove(Player &player) {
		this->players.erase(std::remove(this->players.begin(), this->players.end(), player), this->players.end());
	}

	void Game::turn() {
		// sort by reading order
		sort(begin(this->players), end(players));
		// each player takes turn
		for (auto &player : this->players) {
			// find opponent
			auto opponent = this->opponentFor(player);
			// move towards opponent
			player.move(opponent);
			// attack opponent
			if (player.attack(opponent)) {
				this->remove(opponent);
			}
		}
		// end turn
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
