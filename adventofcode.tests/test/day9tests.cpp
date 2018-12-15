#include "pch.h"

#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>

#include "Day9.h"

using namespace std;

class day9Fixture : public ::testing::Test {

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

	vector<tuple<int, int>> getTokens() {
		vector<tuple<int, int>> records;
		auto reg = regex("(\\d+) players; last marble is worth (\\d+) points", regex_constants::ECMAScript);
		for (int i = 0; i < this->_tokens.size(); i++) {
			smatch match;
			if (regex_match(this->_tokens[i], match, reg)) {
				records.push_back(make_tuple(stoi(match[1]), stoi(match[2])));
			}
		}
		return records;
	}
};

TEST_F(day9Fixture, Part1) {
	SetUp("day9_fixture.txt");
	int players, lastMable;
	tie(players, lastMable) = getTokens()[0];
	auto actual = Day9::Part1(players, lastMable);
	EXPECT_EQ(32, actual);
}
TEST_F(day9Fixture, Part1a) {
	auto actual = Day9::Part1(10, 1618);
	EXPECT_EQ(8317, actual);
}
TEST_F(day9Fixture, Part1b) {
	auto actual = Day9::Part1(13, 7999);
	EXPECT_EQ(146373, actual);
}
TEST_F(day9Fixture, Part1c) {
	auto actual = Day9::Part1(17, 1104);
	EXPECT_EQ(2764, actual);
}
TEST_F(day9Fixture, Part1d) {
	auto actual = Day9::Part1(21, 6111);
	EXPECT_EQ(54718, actual);
}
TEST_F(day9Fixture, Part1e) {
	auto actual = Day9::Part1(30, 5807);
	EXPECT_EQ(37305, actual);
}
// slow test
TEST_F(day9Fixture, DISABLED_Part2) {
	SetUp("day9.txt");
	int players, lastMable;
	tie(players, lastMable) = getTokens()[0];
	auto actual = Day9::Part2(players, lastMable);
	EXPECT_EQ(0, actual);
}
