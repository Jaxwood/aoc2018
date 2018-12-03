#include "pch.h"

#include <fstream>

#include "Day3.h"

class day3Fixture : public ::testing::Test {

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

TEST_F(day3Fixture, Part1) {
	SetUp("day3_fixture.txt");
	auto actual = Day3::Part1();
	EXPECT_EQ(4, actual);
}
