#pragma once

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

namespace Day15 {

	enum PlayerType {
		Elf,
		Goblin
	};

	class Player {
	private:
		int x, y, hitpoints;
		PlayerType playerType;
		bool inRange(Player &player);
	public:
		Player(int x, int y, char type);
		bool takeDamage(Player &player);
		int distance(Player &player);
		void move(Player &player);
		bool dead();
		PlayerType type() { return this->playerType; }
		std::tuple<int, int> position() const;
		bool operator<(Player &other);
	};

	class Game {
	private:
		char grid[7][7];
		std::vector<std::string> lines;
		std::vector<Player> players;
		int turnCount;
		void removeDeadPlayers();
		int opponentFor(Player &player);
	public:
		Game(std::vector<std::string> lines);
		void setup();
		void turn();
		bool over();
		int turns() { return this->turnCount; }
	};

	bool operator==(Player &p1, Player &p2);

	int Part1(std::vector<std::string> lines);
}
