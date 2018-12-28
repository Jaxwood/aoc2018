#pragma once

#include <algorithm>
#include <map>
#include <queue>
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
		void takeDamage();
		bool dead();
		PlayerType type() const { return this->playerType; }
		void move(int x, int y);
		std::tuple<int, int> position() const;
		bool operator<(Player &other);
	};

	class BattleField {
	private:
		char grid[7][7];
		std::vector<Player> players;
		std::vector<Player> targets(Player player);
		std::vector<Player> inRange(std::vector<Player> players);
		std::vector<Player> reachable(Player player, std::vector<Player> players);
		std::vector<std::tuple<int, int>> neighbors(int x, int y);
		bool canReach(std::tuple<int, int> from, std::tuple<int, int> to, std::map<std::tuple<int, int>, std::vector<std::tuple<int, int>>> squares);
		Player nearest(Player player, std::vector<Player> players);
		void chooseMove(Player from, Player to);
	public:
		BattleField();
		void addCoord(int x, int y, char c);
		void move(Player player);
	};

	class Game {
	private:
		BattleField battleField;
		std::vector<Player> players;
		int turnCount;
		void removeDeadPlayers();
		int opponentFor(Player &player);
		bool isBlocked(Player &opponent);
	public:
		Game();
		void setup(std::vector<std::string> lines);
		void turn();
		bool over();
		int turns() { return this->turnCount; }
	};

	bool operator==(Player &p1, Player &p2);

	int Part1(std::vector<std::string> lines);
}
