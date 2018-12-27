#include "pch.h"

#include <fstream>

#include "Day15.h"

using namespace std;
using namespace Day15;

class day15Fixture : public ::testing::Test {

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

TEST_F(day15Fixture, Part1) {
	SetUp("day15_fixture.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(27730, actual);
}
