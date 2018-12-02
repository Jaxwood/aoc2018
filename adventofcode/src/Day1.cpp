#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <map>

#include "Day1.h"

namespace Day1 {

	int convert(std::string token)
	{
		return std::stoi(token);
	}

	int Part1(std::vector<std::string> tokens) {
		auto numbers = std::vector<int>(tokens.size());
		std::transform(std::begin(tokens), std::end(tokens), std::begin(numbers), convert);
		return std::accumulate(std::begin(numbers), std::end(numbers), 0);
	}

	int add(int sum, std::vector<int> &numbers, std::map<int, int> &intermediates)
	{
		for (auto a = 0; a < numbers.size(); a++) {
			sum += numbers[a];
			if (intermediates.count(sum)) {
				return sum;
			}
			intermediates[sum] = sum;
		}
		return add(sum, numbers, intermediates);
	}

	int Part2(std::vector<std::string> tokens) {
		auto numbers = std::vector<int>(tokens.size());
		std::map<int, int> intermediates { std::make_pair(0, 0) };
		std::transform(std::begin(tokens), std::end(tokens), std::begin(numbers), convert);
		return add(0, numbers, intermediates);
	}
}
