#include "pch.h"
#include "Day16.h"

#include <fstream>
#include <regex>
#include <vector>

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

	vector<int> getSegment(int idx, regex reg) {
		vector<int> result;
		smatch match;
		if (regex_match(this->_tokens[idx], match, reg)) {
			result.push_back(stoi(match[1]));
			result.push_back(stoi(match[2]));
			result.push_back(stoi(match[3]));
			result.push_back(stoi(match[4]));
		}
		return result;
	}

	vector<Instruction> getTokens() {
		auto result = vector<Instruction>();
		for (auto i = 0; i < _tokens.size(); i+=4) {
			auto reg = regex("Before:\\s+\\[(\\d+),\\s(\\d+),\\s(\\d+),\\s(\\d+)\\]", regex_constants::ECMAScript);
			auto reg2 = regex("(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)", regex_constants::ECMAScript);
			auto reg3 = regex("After:\\s+\\[(\\d+),\\s(\\d+),\\s(\\d+),\\s(\\d+)\\]", regex_constants::ECMAScript);

			auto before = this->getSegment(i, reg);
			auto operation = this->getSegment(i + 1, reg2);
			auto after = this->getSegment(i + 2, reg3);
			auto instruction = Instruction(before, after, operation);
			result.push_back(instruction);
		}
		return result;
	}
};

TEST_F(day16Fixture, Part1) {
	SetUp("day16_fixture.txt");
	auto actual = Day16::Part1(getTokens());
	EXPECT_EQ(3, actual);
}
