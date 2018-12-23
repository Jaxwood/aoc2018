#include "pch.h"

#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>
#include <iostream>
#include <map>

#include "Day12.h"

using namespace std;
using namespace Day12;

class day12Fixture : public ::testing::Test {

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

	unordered_map<string, string> getTokens() {
		unordered_map<string, string> records;
		auto reg = regex("([.|#]+)\\s=>\\s([#|.])", regex_constants::ECMAScript);
		for (int i = 0; i < this->_tokens.size(); i++) {
			smatch match;
			if (regex_match(this->_tokens[i], match, reg)) {
				records[match[1]] = match[2];
			}
		}
		return records;
	}
};

TEST_F(day12Fixture, Part1) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(20, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ(325, actual);
}

TEST_F(day12Fixture, Part1a) {
	SetUp("day12.txt");
	auto actual = Day12::Part1(20, "#........#.#.#...###..###..###.#..#....###.###.#.#...####..##..##.#####..##...#.#.....#...###.#.####", getTokens());
	EXPECT_EQ(3217, actual);
}

TEST_F(day12Fixture, pattern1) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(0, "#..#.#..##......###...###");
	EXPECT_EQ("..#..", actual);
}

TEST_F(day12Fixture, pattern2) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(1, "#..#.#..##......###...###");
	EXPECT_EQ(".#..#", actual);
}

TEST_F(day12Fixture,  pattern3) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(2, "#..#.#..##......###...###");
	EXPECT_EQ("#..#.", actual);
}

TEST_F(day12Fixture,  pattern4) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(24, "#..#.#..##......###...###");
	EXPECT_EQ("###..", actual);
}

TEST_F(day12Fixture, pattern5) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(23, "#..#.#..##......###...###");
	EXPECT_EQ(".###.", actual);
}

TEST_F(day12Fixture, pattern6) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(25, "#..#.#..##......###...###");
	EXPECT_EQ("##...", actual);
}

TEST_F(day12Fixture, pattern7) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::getPattern(-1, "#..#.#..##......###...###");
	EXPECT_EQ("...#.", actual);
}

TEST_F(day12Fixture,  state01) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(1, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ("#...#....#.....#..#..#..#", Day12::getCurrentState());
}

TEST_F(day12Fixture,  state02) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(2, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ("##..##...##....#..#..#..##", Day12::getCurrentState());
}

TEST_F(day12Fixture,  state03) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(3, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ("#.#...#..#.#....#..#..#...#", Day12::getCurrentState());
}

TEST_F(day12Fixture,  state20) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(20, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ("#....##....#####...#######....#.#..##", Day12::getCurrentState());
}

TEST_F(day12Fixture,  startIdx00) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(0, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ(0, Day12::getStartIdx());
}

TEST_F(day12Fixture,  startIdx01) {
	SetUp("day12_fixture.txt");
	auto actual = Day12::Part1(3, "#..#.#..##......###...###", getTokens());
	EXPECT_EQ(-1, Day12::getStartIdx());
}
