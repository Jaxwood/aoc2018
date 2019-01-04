#include "Day18.h"

using namespace std;

namespace Day18 {
	int dimension = 10;
	char lumberArea[10][10];
	char transformed[10][10];
	const char TREE = '|';
	const char OPEN = '.';
	const char LUMBERYARD = '#';

	void transformOpen(int x, int y) {

	}

	void transformTree(int x, int y) {

	}

	void transformLumberyard(int x, int y) {

	}

	void copy() {
		for (auto y = 0; y < dimension; y++) {
			for (auto x = 0; x < dimension; x++) {
				lumberArea[y][x] = transformed[y][x];
			}
		}
	}

	int sum(char type) {
		int sum = 0;
		for (auto y = 0; y < dimension; y++) {
			for (auto x = 0; x < dimension; x++) {
				if (lumberArea[y][x] == type) {
					sum++;
				}
			}
		}
		return sum;
	}

	void tick() {
		for (auto y = 0; y < dimension; y++) {
			for (auto x = 0; x < dimension; x++) {
				if (lumberArea[y][x] == TREE) {
					transformTree(x, y);
				}
				if (lumberArea[y][x] == OPEN) {
					transformOpen(x, y);
				}
				if (lumberArea[y][x] == LUMBERYARD) {
					transformLumberyard(x, y);
				}
			}
		}
	}

	int Part1(vector<string> lines) {
		for (auto y = 0; y < lines.size(); y++) {
			for (auto x = 0; x < lines[y].size(); x++) {
				lumberArea[y][x] = lines[y][x];
			}
		}

		for (auto i = 0; i < 10; i++) {
			tick();
			copy();
		}

		return sum(TREE) * sum(LUMBERYARD);
	}
}
