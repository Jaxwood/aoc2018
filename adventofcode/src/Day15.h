#pragma once

#include <string>
#include <vector>

namespace Day15 {

	class Creature {
	protected:
		int x, y;
	public:
		Creature(int x, int y);
	};

	class Elv : public Creature {
	public:
		Elv(int x, int y);
	};

	class Goblin : public Creature {
	public:
		Goblin(int x, int y);
	};

	class Dungeon {
	private:
		char grid[7][7];
		std::vector<std::string> lines;
		std::vector<Elv> elves;
		std::vector<Goblin> goblins;
	public:
		Dungeon(std::vector<std::string> lines);
		void setup();
	};

	int Part1(std::vector<std::string> lines);
}
