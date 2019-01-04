#pragma once

#include <map>
#include <string>
#include <vector>

namespace Day17 {
	class Clay {
		std::vector<int> _xs;
		std::vector<int> _ys;
	public:
		Clay(std::vector<int> xs, std::vector<int> ys) : _xs(xs), _ys(ys) {};
		std::vector<int> ys() {
			return this->_ys;
		}
		std::vector<int> xs() {
			return this->_xs;
		}
	};
	int Part1(std::vector<Clay> lines);
	int Part2(std::vector<Clay> lines);
}
