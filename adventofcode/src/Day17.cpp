#include "Day17.h"

using namespace std;

namespace Day17 {
	char ground[15][600];
	int sizeX = 600;
	int sizeY = 15;
	char WATER = '|';
	char SAND = '.';
	char CLAY = '#';

	void fill(int x, int y) {
		bool inSand = false;
		while (!inSand) {
			// go left
			int tempX = x;
			while (ground[y][tempX] != CLAY) {
				ground[y][tempX] = WATER;
				if (ground[y + 1][tempX] == SAND) {
					inSand = true;
					break;
				}
				tempX--;
			}
			// go right
			tempX = x;
			while (ground[y][tempX] != CLAY) {
				ground[y][tempX] = WATER;
				if (ground[y + 1][tempX] == SAND) {
					inSand = true;
					break;
				}
				tempX++;
			}
			y--;
		}
	}

	void flow(int y) {
		for (int x = 0; x < sizeX; x++) {
			if (ground[y - 1][x] == WATER && ground[y][x] == SAND) {
				ground[y][x] = WATER;
			}
		}
	}

	vector<int> inBasin(int y) {
		vector<int> basins;
		for (auto x = 0; x < sizeX; x++) {
			if (ground[y + 1][x] == CLAY && ground[y][x] == WATER && (ground[y][x+1] == SAND || ground[y][x-1] == SAND)) {
				basins.push_back(x);
			}
		}
		return basins;
	}

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
		auto y = 1;
		auto x = 500;
		yMax++;
		ground[0][500] = WATER;
		while (y != yMax) {
			flow(y);
			auto xs = inBasin(y);
			if (xs.size() > 0) {
				for (auto &basin : xs) {
					fill(basin, y);
				}
				y = 0;
			}
			y++;
		}

		// count water tiles
		auto waterTiles = 0;
		for (auto y = 1; y < sizeY; y++) {
			for (auto x = 0; x < sizeX; x++) {
				if(ground[y][x] == WATER) {
					waterTiles++;
				}
			}
		}
		return waterTiles;

	}
}
