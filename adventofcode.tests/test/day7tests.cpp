#include "pch.h"

#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>

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

	std::vector<std::tuple<std::string, std::string>> getTokens() {
		std::vector<std::tuple<std::string, std::string>> records;
		auto reg = std::regex("Step\\s(\\w+)\\smust be finished before step\\s(\\w+)\\scan begin.", std::regex_constants::ECMAScript);
		for (int i = 0; i < this->_tokens.size(); i++) {
			std::smatch match;
			if (std::regex_match(this->_tokens[i], match, reg)) {
				records.push_back(std::make_tuple(match[1], match[2]));
			}
		}
		return records;
	}
};

TEST_F(day7Fixture, Part1) {
	SetUp("day7_fixture.txt");
	auto actual = Day7::Part1(getTokens());
	EXPECT_EQ("CABDFE", actual);
}

TEST_F(day7Fixture, Part2) {
	SetUp("day7_fixture.txt");
	auto actual = Day7::Part2(getTokens(), 2);
	EXPECT_EQ(15, actual);
}
