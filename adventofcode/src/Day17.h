#pragma once

#include <string>
#include <vector>

namespace Day17 {
	class Clay {
		std::vector<int> xs;
		std::vector<int> ys;
	public:
		Clay(std::vector<int> xs, std::vector<int> ys) : xs(xs), ys(ys) {};
	};
	int Part1(std::vector<Clay> lines);
}
