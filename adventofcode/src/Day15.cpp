#include "Day15.h"

using namespace std;

namespace Day15 {
	
	Player::Player(int x, int y, char type) {
		this->x = x;
		this->y = y;
		this->hitpoints = 200;
		this->type = type == 'E' ? Elv : Goblin;
	}

	void Player::attack(Player &creature) {
		creature.damage();
	}

	void Player::damage() {
		this->hitpoints -= 3;
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

	void Game::turn() {
		// sort by reading order
		sort(begin(this->players), end(players));
		// move each player
		// attack with each player
		// end turn
		this->turnCount++;
	}

	bool Game::over() {
		return true;
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
