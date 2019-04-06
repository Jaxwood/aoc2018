#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <regex>

#include "Day23.h"

using namespace std;
using namespace Day23;

class day23Fixture : public ::testing::Test {

private:
	std::vector<std::string> _tokens;

public:
	void SetUp(std::string path) {
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

		_tokens = tokens;
	}

	vector<Point> getTokens() {
		auto result = vector<Point>();
		auto reg = regex("pos=<(-?\\d+),(-?\\d+),(-?\\d+)>,\\sr=(\\d+)", regex_constants::ECMAScript);
		for (auto &token : _tokens) {
			smatch match;
			if (regex_match(token, match, reg)) {
				result.push_back(Point(stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])));
			}
		}
		return result;
	}
};

TEST_F(day23Fixture, Part1) {
	SetUp("day23_input.txt");
	auto actual = Day23::Part1(getTokens());
	EXPECT_EQ(7, actual);
}
