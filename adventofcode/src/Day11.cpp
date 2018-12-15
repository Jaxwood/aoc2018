#include "Day11.h"

using namespace std;

namespace Day11 {

	tuple<int, int> Part1(int size, int serialNumber) {
		int best = 0;
		auto grid = Grid(serialNumber);

		tuple<int, int> candidate;
		for (int x = 1; x <= 300 - size; x++) {
			for (int y = 1; y <= 300 - size; y++) {
				auto result = grid.totals(x, y, size);
				if (result > best) {
					best = result;
					candidate = make_tuple(x, y);
				}
			}
		}
		return candidate;
	}

	tuple<int, int, int> Part2(int serialNumber) {
		tuple<int, int, int> candidate;
		int best = 0;
		auto grid = Grid(serialNumber);

		for (int size = 1; size <= 301; size++) {
			for (int x = 1; x <= 300 - size; x++) {
				for (int y = 1; y <= 300 - size; y++) {
					auto result = grid.totals(x, y, size);
					if (result > best) {
						best = result;
						candidate = make_tuple(x, y, size);
					}
				}
			}
		}
		return candidate;
	}
}
