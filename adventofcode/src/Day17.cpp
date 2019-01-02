#include "Day17.h"

using namespace std;

namespace Day17 {
	int Part1(vector<Clay> lines) {
		// transform clays to a map data structure
		map<int, vector<int>> veins;
		for (auto &clay : lines) {
			for (auto &y : clay.ys()) {
				for (auto &x : clay.xs()) {
					veins[y].push_back(x);
				}
			}
		}

		int sizeX = 600;
		int sizeY = 15;
		char WATER = '|';
		char SAND = '.';
		char CLAY = '#';

		char ground[15][600];
		// add sand tiles to the ground
		for (auto y = 0; y < sizeY; y++) {
			for (auto x = 0; x < sizeX; x++) {
				ground[y][x] = SAND;
			}
		}
		// add clay tiles to the ground
		auto yMax = 0;
		for (auto &vein : veins) {
			for (auto xs : vein.second) {
				ground[vein.first][xs] = CLAY;
			}
			yMax = vein.first;
		}

		// fill water
		auto y = 0;
		auto x = 500;
		yMax++;
		while (y != yMax) {
			// fill water until hitting clay
			if (ground[y][x] == SAND) {
				ground[y][x] = WATER;
				y++;
			}
			else {
				// fill basin
				y--;
				auto xTemp = x;
				// go left
				while (ground[y][xTemp] != CLAY) {
					ground[y][xTemp] = WATER;
					xTemp--;
					if (ground[y + 1][xTemp] == SAND) {
						x = xTemp;
						break;
					}
				}
				// go right
				xTemp = x;
				while (ground[y][xTemp] != CLAY) {
					ground[y][xTemp] = WATER;
					xTemp++;
					if (ground[y + 1][xTemp] == SAND) {
						x = xTemp;
						break;
					}
				}
			}
		}

		// count water tiles
		auto waterTiles = 0;
		for (auto y = 0; y < sizeY; y++) {
			for (auto x = 0; x < sizeX; x++) {
				if(ground[y][x] == WATER) {
					waterTiles++;
				}
			}
		}
		return waterTiles;

	}
}
