#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>

#include "Day18.h"

using namespace std;
using namespace Day18;

class day18Fixture : public ::testing::Test {

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

	vector<string> getTokens() {
		return _tokens;
	}
};

TEST_F(day18Fixture, Part1) {
	SetUp("day18_part1.txt");
	auto actual = Day18::Part1(getTokens());
	EXPECT_EQ(574200, actual);
}
TEST_F(day18Fixture, Part2) {
	auto actual = Day18::Part2();
	EXPECT_EQ(211653, actual);
}
