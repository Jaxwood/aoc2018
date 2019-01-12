#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace Day20 {
	typedef std::tuple<int, int> Point;

	std::vector<std::string> paths(std::vector<std::string> acc, std::string raw);
	int Part1(std::string input);
}
