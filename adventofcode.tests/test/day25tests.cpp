#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <regex>

#include "Day25.h"

using namespace std;
using namespace Day25;

class day25Fixture : public ::testing::Test {

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
		auto reg = regex("(-?\\d+),(-?\\d+),(-?\\d+),(-?\\d+)", regex_constants::ECMAScript);
		for (auto &token : _tokens) {
			smatch match;
			if (regex_match(token, match, reg)) {
				result.push_back(make_tuple(stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])));
			}
		}
		return result;
	}
};

TEST_F(day25Fixture, Part1a) {
	SetUp("part1a.txt");
	auto actual = Day25::Part1(getTokens());
	EXPECT_EQ(4, actual);
}

TEST_F(day25Fixture, Part1b) {
	SetUp("part1b.txt");
	auto actual = Day25::Part1(getTokens());
	EXPECT_EQ(3, actual);
}

TEST_F(day25Fixture, Part1c) {
	SetUp("part1c.txt");
	auto actual = Day25::Part1(getTokens());
	EXPECT_EQ(8, actual);
}
