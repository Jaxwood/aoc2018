#include <algorithm>
#include <iterator>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <vector>

namespace Day22 {
	enum ErosionLevel {
		Rocky = 0,
		Wet = 1,
		Narrow = 2
	};

	enum Tools {
		Torch = 0,
		ClimbingGear = 1,
		Neither = 2
	};

	int Part1(std::tuple<int, int> target, int depth);
	int Part2(std::tuple<int, int> target, int depth);
}
