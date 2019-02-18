#include "Day22.h"

using namespace std;

namespace Day22 {
	map<tuple<int, int>, long long> erosionLevels;

	map<int, ErosionLevel> cavernTypes = {
		{ 0, Rocky },
		{ 1, Wet },
		{ 2, Narrow }
	};

	long long CalculateErosionLevel(tuple<int, int> target, int depth, size_t x, size_t y) {
		int targetX, targetY;
		tie(targetX, targetY) = target;
		long long geologicalIndex;
		if (x == 0 && y == 0) {
			geologicalIndex = 0;
		}
		else if (x == targetX && y == targetY) {
			geologicalIndex = 0;
		}
		else if (x == 0) {
			geologicalIndex = y * 48271;
		}
		else if (y == 0) {
			geologicalIndex = x * 16807;
		}
		else {
			geologicalIndex = erosionLevels[make_tuple(x - 1, y)] * erosionLevels[make_tuple(x, y - 1)];
		}

		erosionLevels[make_tuple(x, y)] = (geologicalIndex + depth) % 20183;
		return erosionLevels[make_tuple(x, y)];
	}

	int Part1(tuple<int, int> target, int depth) {
		int sum = 0;
		ErosionLevel cavern[11][11];
		for (size_t x = 0; x <= 10; x++) {
			for (size_t y = 0; y <= 10; y++) {
				auto erosionLevel = CalculateErosionLevel(target, depth, x, y);
				cavern[y][x] = cavernTypes[erosionLevel % 3];
				sum += (int)cavern[y][x];
			}
		}

		return sum;
	}
}
