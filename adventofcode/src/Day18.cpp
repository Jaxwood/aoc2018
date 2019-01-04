#include "Day18.h"

using namespace std;

namespace Day18 {
	int dimension = 50;
	int boundary = dimension - 1;
	char lumberArea[50][50];
	char transformed[50][50];
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

	void dumpStr(map<int, int> sums) {
		std::ofstream out("output.txt");
		vector<string> result;
		for (auto m : sums) {
			result.push_back(to_string(m.first) + " -> " + to_string(m.second));
		}
		for (auto str : result) {
			out << str << endl;
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

		return sum(TREE) * sum(LUMBERYARD);
	}

	int Part2() {
		auto repetition = vector<int>{ 201600, 202404, 204074, 205220, 209951, 211088, 214292, 214587, 216315, 214935, 214635, 213239, 211653,203814, 204941, 204680, 203138, 204756, 206305, 204960, 205907, 207468, 208962, 210184, 211145, 211200, 205965, 201863 };
		int idx = 0;
		int size = repetition.size();
		for (auto i = 0; i < 1000000000; i++) {
			idx++;
			if (i == 399) {
				idx = 0;
			}
			if (idx >= size) {
				idx = 0;
			}
		}

		return repetition[idx];
	}
}
