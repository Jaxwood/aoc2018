#include "Day15.h"

using namespace std;

namespace Day15 {
	
	Creature::Creature(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Elv::Elv(int x, int y) : Creature(x, y) {}

	Goblin::Goblin(int x, int y) : Creature(x, y) {}

	Dungeon::Dungeon(vector<string> lines) {
		this->lines = lines;
	}

	void Dungeon::setup() {
		char grid[7][7];
		for (int y = 0; y < lines.size(); y++) {
			for (int x = 0; x < lines[y].size(); x++) {
				auto candidate = lines[y][x];
				if (candidate == 'E') {
					this->elves.push_back(Elv(x, y));
					this->grid[x][y] = '.';
				}
				else if (candidate == 'G') {
					this->goblins.push_back(Goblin(x,y));
					this->grid[x][y] = '.';

				}
				else {
					this->grid[x][y] = candidate;
				}
			}
		}
	}

	int Part1(vector<string> lines) {
		auto dungeon = Dungeon(lines);
		dungeon.setup();
		return 0;
	}
}
