#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace Day15 {

	enum PlayerType {
		Elv,
		Goblin
	};

	class Player {
	protected:
		int x, y, hitpoints;
		PlayerType type;
	public:
		Player(int x, int y, char type);
		void attack(Player &creature);
		void damage();
		bool operator<(Player &other);
	};

	class Game {
	private:
		char grid[7][7];
		std::vector<std::string> lines;
		std::vector<Player> players;
		int turnCount;
	public:
		Game(std::vector<std::string> lines);
		void setup();
		void turn();
		bool over();
		int turns() { return this->turnCount; }
	};

	int Part1(std::vector<std::string> lines);
}
