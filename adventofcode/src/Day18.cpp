#include "Day18.h"

using namespace std;

namespace Day18 {
	int dimension = 10;
	int boundary = dimension - 1;
	char lumberArea[10][10];
	char transformed[10][10];
	const char TREE = '|';
	const char OPEN = '.';
	const char LUMBERYARD = '#';

	void dump() {
		std::ofstream out("output.txt");
		vector<string> result;
		for (auto y = 0; y < dimension; y++) {
			string text = "";
			for (auto x = 0; x < dimension; x++) {
				text += lumberArea[y][x];
			}
			result.push_back(text);
		}
		for (auto &line : result) {
			out << line << endl;
		}
	}

	int sumTree(int x, int y) {
		int sum = 0;
		if (y > 0 && lumberArea[y-1][x] == TREE) {
			sum++;
		}
		if (y > 0 && x > 0 && lumberArea[y - 1][x - 1] == TREE) {
			sum++;
		}
		if (y > 0 && x < boundary && lumberArea[y - 1][x + 1] == TREE) {
			sum++;
		}
		if (y < boundary && lumberArea[y + 1][x] == TREE) {
			sum++;
		}
		if (x > 0 && lumberArea[y][x - 1] == TREE) {
			sum++;
		}
		if (x < boundary && lumberArea[y][x + 1] == TREE) {
			sum++;
		}
		if (y < boundary && x > 0 && lumberArea[y + 1][x - 1] == TREE) {
			sum++;
		}
		if (y < boundary && x < boundary && lumberArea[y + 1][x + 1] == TREE) {
			sum++;
		}
		return sum;
	}

	int sumLumberyard(int x, int y) {
		int sum = 0;
		if (y > 0 && lumberArea[y-1][x] == LUMBERYARD) {
			sum++;
		}
		if (y > 0 && x > 0 && lumberArea[y - 1][x - 1] == LUMBERYARD) {
			sum++;
		}
		if (y > 0 && x < boundary && lumberArea[y - 1][x + 1] == LUMBERYARD) {
			sum++;
		}
		if (y < boundary && lumberArea[y + 1][x] == LUMBERYARD) {
			sum++;
		}
		if (x > 0 && lumberArea[y][x - 1] == LUMBERYARD) {
			sum++;
		}
		if (x < boundary && lumberArea[y][x + 1] == LUMBERYARD) {
			sum++;
		}
		if (y < boundary && x > 0 && lumberArea[y + 1][x - 1] == LUMBERYARD) {
			sum++;
		}
		if (y < boundary && x < boundary && lumberArea[y + 1][x + 1] == LUMBERYARD) {
			sum++;
		}
		return sum;
	}

	void transformOpen(int x, int y) {
		int sum = sumTree(x, y);
		if (sum >= 3) {
			transformed[y][x] = TREE;
		}
		else {
			transformed[y][x] = OPEN;
		}
	}

	void transformTree(int x, int y) {
		int sum = sumLumberyard(x, y);
		if (sum >= 3) {
			transformed[y][x] = LUMBERYARD;
		}
		else {
			transformed[y][x] = TREE;
		}
	}

	void transformLumberyard(int x, int y) {
		int lumberyards = sumLumberyard(x, y);
		int trees = sumTree(x, y);
		if (lumberyards > 0 && trees > 0) {
			transformed[y][x] = LUMBERYARD;
		}
		else {
			transformed[y][x] = OPEN;
		}
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

		// dump();

		return sum(TREE) * sum(LUMBERYARD);
	}
}
