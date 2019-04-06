#include <algorithm>
#include <iterator>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#include <fstream>
#include <iostream>
#include <string>

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

	class Cave {
		std::tuple<int, int> target;
		int depth;
		long long calculateErosionLevel(size_t x, size_t y);
		Tools switchTool(Tools tool, std::set<Tools> tools);
	public:
		Cave(int depth, std::tuple<int, int> target);
		int sum();
		std::vector<std::tuple<int, int>> getNeighbors(std::tuple<int, int> from);
		std::tuple<int,Tools> getTravelCost(Tools equipment, std::tuple<int, int> from, std::tuple<int, int> to);
	};

	int Part1(std::tuple<int, int> target, int depth);
	int Part2(std::tuple<int, int> target, int depth);
}
