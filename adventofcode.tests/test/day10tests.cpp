#include "pch.h"

#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>

#include "Day10.h"

using namespace std;
using namespace Day10;

class day10Fixture : public ::testing::Test {

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

	vector<Point> getTokens() {
		vector<Point> records;
		auto reg = regex("position=<([-|\\s]?\\d+), ([-|\\s]?\\d+)> velocity=<([-|\\s]?\\d+), ([-|\\s]?\\d+)>", regex_constants::ECMAScript);
		for (int i = 0; i < this->_tokens.size(); i++) {
			smatch match;
			if (regex_match(this->_tokens[i], match, reg)) {
				records.push_back(Point(stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])));
			}
		}
		return records;
	}
};

TEST_F(day10Fixture, Part1) {
	SetUp("day10.txt");
	auto actual = Day10::Part1(getTokens(), 3);
	std::ofstream out("output_1.txt");
	for (auto &line : actual) {
		out << line << endl;
	}
	EXPECT_EQ(vector<string>(), actual);
}
