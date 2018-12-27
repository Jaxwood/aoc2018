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
	public:
		Player(int x, int y, char type);
		bool inRange(const Player *player);
		bool attack(Player &player);
		bool takeDamage();
		void move(Player player);
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
	public:
		Game(std::vector<std::string> lines);
		void setup();
		void turn();
		bool over();
		void remove(Player &player);
		int turns() { return this->turnCount; }
		Player& opponentFor(Player &player);
	};

	bool operator==(Player &p1, Player &p2);

	int Part1(std::vector<std::string> lines);
}
