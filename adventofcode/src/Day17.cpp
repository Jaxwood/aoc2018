#include "Day17.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace Day17 {
	char ground[15][600];
	int sizeX = 600;
	int sizeY = 15;
	char WATER = '|';
	char SAND = '.';
	char CLAY = '#';

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
		return isSand(x, y+1);
	}

	void addWater(int x, int y) {
		ground[y][x] = WATER;
	}

	void addWaterLeft(int x, int y) {
		while (true) {
			x--;
			if (isClay(x,y)) {
				break;
			}
			addWater(x, y);
			if (isEdge(x, y)) {
				break;
			}
		}
	}

	void addWaterRight(int x, int y) {
		while (true) {
			x++;
			if (isClay(x,y)) {
				break;
			}
			addWater(x, y);
			if (isEdge(x, y)) {
				break;
			}
		}
	}

	vector<int> waterAbove(int y) {
		vector<int> edges;
		for (int x = 0; x < sizeX; x++) {
			if (isSand(x, y) && isWater(x, y - 1)) {
				edges.push_back(x);
			}
		}
		return edges;
	}

	vector<int> findEdges(int y) {
		vector<int> edges;
		for (int x = 0; x < sizeX; x++) {
			if (isWater(x, y) && isSand(x, y + 1)) {
				edges.push_back(x);
			}
		}
		return edges;
	}

	void dump() {
		std::ofstream out("output.txt");
		vector<string> result;
		for (auto y = 1; y < sizeY; y++) {
			string text = "";
			for (auto x = 475; x < 525; x++) {
				text += ground[y][x];
			}
			result.push_back(text);
		}
		for (auto &line : result) {
			out << line << endl;
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
		for (auto &vein : veins) {
			for (auto xs : vein.second) {
				ground[vein.first][xs] = CLAY;
			}
			yMax = vein.first;
		}

		ground[0][500] = WATER;
		int y = 1;
		int x = 500;
		yMax++;
		while (y != yMax) {
			if (isSand(x, y)) {
				auto xs = waterAbove(y);
				if (xs.size() == 0) {
					addWater(x, y);
				}
				else {
					for (int i = 0; i < xs.size(); i++) {
						x = xs[i];
						addWater(x, y);
					}
				}
				y++;
			}
			else {
				y--;
				addWaterLeft(x, y);
				addWaterRight(x, y);

				auto xs = findEdges(y);
				if (xs.size() > 0) {
					y++;
					for (int i = 0; i < xs.size(); i++) {
						x = xs[i];
					}
					// y++;
				}
			}
			dump();
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
