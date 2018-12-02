#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <map>

#include "Day1.h"

namespace Day1 {

	std::vector<std::string> parse(std::string path)
	{
		std::vector<std::string> tokens;
		std::string line;
		std::ifstream stream;
		stream.open(path, std::iostream::in);
		while (std::getline(stream, line))
		{
			tokens.push_back(line);
		}

		if (stream.is_open())
		{
			stream.close();
		}

		return tokens;
	}

	int convert(std::string token)
	{
		return std::stoi(token);
	}

	int Part1(std::string path) {
		auto lines = parse(path);
		auto numbers = std::vector<int>(lines.size());
		std::transform(std::begin(lines), std::end(lines), std::begin(numbers), convert);
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

	int Part2(std::string path) {
		auto lines = parse(path);
		auto numbers = std::vector<int>(lines.size());
		std::map<int, int> intermediates { std::make_pair(0, 0) };
		std::transform(std::begin(lines), std::end(lines), std::begin(numbers), convert);
		return add(0, numbers, intermediates);
	}
}
