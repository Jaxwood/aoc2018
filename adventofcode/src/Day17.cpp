#include "Day17.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace Day17 {
	char ground[2000][2000];
	int sizeX = 2000;
	int sizeY = 2000;
	char WATER = '|';
	char SAND = '.';
	char CLAY = '#';

	void dump() {
		std::ofstream out("output.txt");
		vector<string> result;
		for (auto y = 1; y < sizeY; y++) {
			string text = "";
			for (auto x = 0; x < sizeX; x++) {
				text += ground[y][x];
			}
			result.push_back(text);
		}
		for (auto &line : result) {
			out << line << endl;
		}
	}

	bool isSand(int x, int y) {
		return ground[y][x] == SAND;
	}

	bool isWater(int x, int y) {
		return ground[y][x] == WATER;
	}

	bool isClay(int x, int y) {
		return ground[y][x] == CLAY;
	}

	bool isEdge(int x, int y) {
		if (isSand(x, y + 1)) {
			return true;
		}
		while (isWater(x, y)) {
			y++;
			if (isSand(x, y)) {
				return true;
			}
		}
		return false;
	}

	void addWater(int x, int y) {
		ground[y][x] = WATER;
	}

	bool addWaterLeft(int x, int y) {
		while (true) {
			if (isClay(x,y)) {
				return false;
			}
			addWater(x, y);
			if (isEdge(x, y)) {
				return true;
			}
			x--;
		}
	}

	bool addWaterRight(int x, int y) {
		while (true) {
			if (isClay(x,y)) {
				return false;
			}
			addWater(x, y);
			if (isEdge(x, y)) {
				return true;
			}
			x++;
		}
	}

	vector<int> drip(int y) {
		vector<int> edges;
		for (int x = 0; x < sizeX; x++) {
			if (isSand(x, y) && isWater(x, y - 1)) {
				edges.push_back(x);
			}
		}
		return edges;
	}

	void fillBasin(int x, int y) {
		auto left = addWaterLeft(x, y);
		auto right = addWaterRight(x, y);
		if (left || right) {
			return;
		}
		return fillBasin(x, y - 1);
	}

	bool isBasin(int x, int y) {
		if (isClay(x, y)) {
			return true;
		}
		while (isWater(x, y)) {
			y++;
			if(isClay(x,y)) {
				return true;
			}
		}
		return false;
	}

	int findWaterSource() {
		for (auto y = 1; y < sizeY; y++) {
			auto water = drip(y);
			if (water.size() > 0) {
				return y - 1;
			}
		}
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
		auto yMin = INT_MAX;
		for (auto &vein : veins) {
			for (auto xs : vein.second) {
				ground[vein.first][xs] = CLAY;
			}
			if (vein.first < yMin) {
				yMin = vein.first;
			}
			yMax = vein.first;
		}

		ground[0][500] = WATER;
		int y = 1;
		int x = 500;
		yMax++;
		while (y != yMax) {
			auto xs = drip(y);
			for (auto x : xs) {
				if (isBasin(x, y + 1)) {
					fillBasin(x, y);
					y = findWaterSource();
				}
				else {
					addWater(x, y);
				}
			}
			y++;
		}
		dump();

		// count water tiles
		auto waterTiles = 0;
		for (auto y = yMin; y < sizeY; y++) {
			for (auto x = 0; x < sizeX; x++) {
				if(ground[y][x] == WATER) {
					waterTiles++;
				}
			}
		}
		return waterTiles;

	}
}
