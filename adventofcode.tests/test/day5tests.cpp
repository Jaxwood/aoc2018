#include "pch.h"

#include <fstream>
#include <regex>

#include "Day5.h"

class day5Fixture : public ::testing::Test {

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

	std::string getTokens() {
		return _tokens[0];
	}
};

TEST_F(day5Fixture, Part1) {
	SetUp("day5_fixture.txt");
	auto actual = Day5::Part1(getTokens());
	EXPECT_EQ(10, actual);
}

TEST_F(day5Fixture, Part2) {
	SetUp("day5_fixture.txt");
	auto actual = Day5::Part2(getTokens());
	EXPECT_EQ(4, actual);
}
