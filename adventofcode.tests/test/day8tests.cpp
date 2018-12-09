#include "pch.h"

#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>

#include "Day8.h"

class day8Fixture : public ::testing::Test {

private:
	std::vector<std::string> _tokens;

public:
	void SetUp(std::string path) {
		std::vector<std::string> tokens;
		std::string line;
		std::ifstream stream;
		stream.open(path, std::iostream::in);
		while (std::getline(stream, line, ' '))
		{
			tokens.push_back(line);
		}

		if (stream.is_open())
		{
			stream.close();
		}

		_tokens = tokens;
	}

	vector<int> getTokens() {
		vector<int> records;
		transform(begin(this->_tokens), end(this->_tokens), back_inserter(records), [](auto str) {
			return stoi(str);
		});
		reverse(begin(records), end(records));
		return records;
	}
};

TEST_F(day8Fixture, Part1) {
	SetUp("day8_fixture.txt");
	auto actual = Day8::Part1(getTokens());
	EXPECT_EQ(138, actual);
}

TEST_F(day8Fixture, Part2) {
	SetUp("day8_fixture.txt");
	auto actual = Day8::Part2(getTokens());
	EXPECT_EQ(66, actual);
}
