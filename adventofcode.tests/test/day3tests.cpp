#include "pch.h"

#include <fstream>
#include <regex>

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

	std::vector<Day3::Fabric> getTokens() {
		std::vector<Day3::Fabric> fabrics;
		auto reg = std::regex("#(\\d+)\\s@\\s(\\d+),(\\d+):\\s(\\d+)x(\\d+)", std::regex_constants::ECMAScript);
		for(int i = 0; i < _tokens.size(); i++) {
			std::smatch match;
			if (std::regex_match(_tokens[i], match, reg)) {
				fabrics.push_back(Day3::Fabric(
					std::stoi(match[1]),
					std::stoi(match[2]),
					std::stoi(match[3]),
					std::stoi(match[4]),
					std::stoi(match[5])));
			}
		}

		return fabrics;
	}
};

TEST_F(day3Fixture, Part1) {
	SetUp("day3_fixture.txt");
	auto actual = Day3::Part1(getTokens());
	EXPECT_EQ(4, actual);
}

TEST_F(day3Fixture, Part2) {
	SetUp("day3_fixture.txt");
	auto actual = Day3::Part2(getTokens());
	EXPECT_EQ(3, actual);
}
