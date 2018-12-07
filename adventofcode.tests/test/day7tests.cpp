#include "pch.h"

#include <fstream>
#include <algorithm>

#include "Day7.h"

class day7Fixture : public ::testing::Test {

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
		return this->_tokens;
	}
};

TEST_F(day7Fixture, Part1) {
	SetUp("day7_fixture.txt");
	auto actual = Day7::Part1(getTokens());
	EXPECT_EQ("CABDFE", actual);
}
