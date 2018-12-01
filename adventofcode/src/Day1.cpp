#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

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

	int Sum(std::string path) {
		auto lines = parse(path);
		std::vector<int> target = std::vector<int>(lines.size());
		 std::transform(std::begin(lines), std::end(lines), std::begin(target), convert);
		return std::accumulate(std::begin(target), std::end(target), 0);
	}
}
