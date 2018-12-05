#include "pch.h"

#include <fstream>
#include <regex>

#include "Day4.h"

class day4Fixture : public ::testing::Test {

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

	std::vector<Day4::Record> getTokens() {

		std::vector<Day4::Record> records;
		auto reg = std::regex("\\[(\\d+)-(\\d+)-(\\d+)\\s(\\d+):(\\d+)\\]\\s(.*)", std::regex_constants::ECMAScript);
		auto grd = std::regex("\\w+\\s\\#(\\d+).*");
		auto slp = std::regex("falls asleep");
		auto awk = std::regex("wakes up");
		for (int i = 0; i < _tokens.size(); i++) {
			std::smatch match;
			if (std::regex_match(_tokens[i], match, reg)) {
				int id = 0;
				std::string instruction = match[6];
				std::smatch guard;
				std::smatch sleep;
				std::smatch awake;

				if (std::regex_match(instruction, guard, grd))
				{
					id = std::stoi(guard[1]);
				}
				records.push_back(Day4::Record(
					std::stoi(match[1]),
					std::stoi(match[2]),
					std::stoi(match[3]),
					std::stoi(match[4]),
					std::stoi(match[5]),
					id,	
					std::regex_match(instruction, sleep, slp),
					std::regex_match(instruction, awake, awk)
				));
			}
		}

		return records;
	}
};

TEST_F(day4Fixture, Part1) {
	SetUp("day4_fixture.txt");
	auto actual = Day4::Part1(getTokens());
	EXPECT_EQ(240, actual);
}

TEST_F(day4Fixture, Part2) {
	SetUp("day4_fixture.txt");
	auto actual = Day4::Part2(getTokens());
	EXPECT_EQ(4455, actual);
}
