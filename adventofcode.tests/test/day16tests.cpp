#include "pch.h"
#include "Day16.h"

#include <vector>
#include <fstream>

using namespace std;
using namespace Day16;

class day16Fixture : public ::testing::Test {

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

TEST_F(day16Fixture, Part1) {
	SetUp("day16_fixture.txt");
	auto actual = Day16::Part1(getTokens());
	EXPECT_EQ(0, actual);
}
