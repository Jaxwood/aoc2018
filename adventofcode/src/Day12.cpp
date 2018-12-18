#include "Day12.h"


namespace Day12 {

	int Part1(string state, unordered_map<string, string> rules) {
		auto garden = Garden(state, rules);

		for (int g = 0; g < 20; g++) {
			garden.grow();
		}

		return garden.plants();
	}
}
