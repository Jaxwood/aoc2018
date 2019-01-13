#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <regex>

#include "Day20.h"

using namespace std;
using namespace Day20;

class day20Fixture : public ::testing::Test {

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

	string getTokens() {
		return _tokens[0];
	}
};

TEST_F(day20Fixture, Part1) {
	SetUp("day20_part1.txt");
	auto actual = Day20::Part1(getTokens());
	EXPECT_EQ(31, actual);
}

TEST_F(day20Fixture, Part1a) {
	auto actual = Day20::Part1("^WSSEESWWWNW(S|NENNEEEENN(ESSSSW(NWSW|SSEN)|WSWWN(E|WWS(E|SS))))$");
	EXPECT_EQ(31, actual);
}

TEST_F(day20Fixture, Part1b) {
	auto actual = Day20::Part1("^ESSWWN(E|NNENN(EESS(WNSE|)SSS|WWWSSSSE(SW|NNNE)))$");
	EXPECT_EQ(23, actual);
}

TEST_F(day20Fixture, Part1c) {
	auto actual = Day20::Part1("^WNE$");
	EXPECT_EQ(3, actual);
}

TEST_F(day20Fixture, Part1d) {
	auto actual = Day20::Part1("^ENWWW(NEEE|SSE(EE|N))$");
	EXPECT_EQ(10, actual);
}

TEST_F(day20Fixture, Part1e) {
	auto actual = Day20::Part1("^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$");
	EXPECT_EQ(18, actual);
}
