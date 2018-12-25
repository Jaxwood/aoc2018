#include "pch.h"

#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>
#include <iostream>
#include <map>

#include "Day13.h"

using namespace std;
using namespace Day13;

class day13Fixture : public ::testing::Test {

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

TEST_F(day13Fixture, Part1) {
	SetUp("day13_fixture.txt");
	auto actual = Day13::Part1(getTokens());
	EXPECT_EQ(make_tuple(7,3), actual);
}
