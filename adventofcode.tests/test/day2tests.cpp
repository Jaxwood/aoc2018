#include "pch.h"

#include <fstream>

#include "Day2.h"

class day2Fixture : public ::testing::Test {

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

	std::vector<std::string> getTokens() {
		return _tokens;
	}
};

TEST_F(day2Fixture, Part1) {
	SetUp("day2_fixture_1.txt");
	auto actual = Day2::Part1(getTokens());
	EXPECT_EQ(12, actual);
}

TEST_F(day2Fixture, Part2) {
	SetUp("day2_fixture_1.txt");
	auto actual = Day2::Part2(getTokens());
	EXPECT_EQ("fgij", actual);
}
