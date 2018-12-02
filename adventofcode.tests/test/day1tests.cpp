#include "pch.h"

#include <fstream>

#include "Day1.h"

class day1Fixture : public ::testing::Test {

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

TEST_F(day1Fixture, Example1) {
	SetUp("day1_fixture_1.txt");
	auto actual = Day1::Part1(getTokens());
	EXPECT_EQ(0, actual);
}

TEST_F(day1Fixture, Example2) {
	SetUp("day1_fixture_2.txt");
	auto actual = Day1::Part1(getTokens());
	EXPECT_EQ(3, actual);
}

TEST_F(day1Fixture, Example3) {
	SetUp("day1_fixture_3.txt");
	auto actual = Day1::Part1(getTokens());
	EXPECT_EQ(-6, actual);
}

TEST_F(day1Fixture, Part2_Example1) {
	SetUp("day1_part2_1.txt");
	auto actual = Day1::Part2(getTokens());
	EXPECT_EQ(0, actual);
}

TEST_F(day1Fixture, Part2_Example2) {
	SetUp("day1_part2_2.txt");
	auto actual = Day1::Part2(getTokens());
	EXPECT_EQ(10, actual);
}

TEST_F(day1Fixture, Part2_Example3) {
	SetUp("day1_part2_3.txt");
	auto actual = Day1::Part2(getTokens());
	EXPECT_EQ(5, actual);
}

TEST_F(day1Fixture, Part2_Example4) {
	SetUp("day1_part2_4.txt");
	auto actual = Day1::Part2(getTokens());
	EXPECT_EQ(14, actual);
}