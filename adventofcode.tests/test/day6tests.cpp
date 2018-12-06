#include "pch.h"

#include <fstream>
#include <algorithm>

#include "Day6.h"

class day6Fixture : public ::testing::Test {

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

	std::vector<Day6::Coord> getTokens() {
		std::vector<Day6::Coord> result(this->_tokens.size());
		std::transform(std::begin(this->_tokens), std::end(this->_tokens), std::begin(result), [](std::string token) {
			auto idx = token.find(',');
			auto x = std::stoi(token.substr(0, idx));
			auto y = std::stoi(token.substr(idx+1));
			return Day6::Coord(x, y);
		});
		return result;
	}
};

TEST_F(day6Fixture, Part1) {
	SetUp("day6_fixture.txt");
	auto actual = Day6::Part1(getTokens());
	EXPECT_EQ(17, actual);
}
