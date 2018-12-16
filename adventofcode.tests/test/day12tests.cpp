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

	map<string, string> getTokens() {
		map<string, string> records;
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
	auto actual = Day12::Part1("#..#.#..##......###...###", getTokens());
	EXPECT_EQ(325, actual);
}
