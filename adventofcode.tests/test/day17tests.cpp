#include "pch.h"
#include "Day17.h"

#include <fstream>
#include <numeric>
#include <regex>
#include <vector>

using namespace std;
using namespace Day17;

class day17Fixture : public ::testing::Test {

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

	vector<Clay> getTokens() {
		vector<Clay> result;
		auto reg = regex("([x,y])=(\\d+),\\s[x,y]=(\\d+)..(\\d+)", regex_constants::ECMAScript);
		for (int i = 0; i < this->_tokens.size(); i++) {
			smatch match;
			if (regex_match(this->_tokens[i], match, reg)) {
				if (match[1] == "x") {
					auto from = stoi(match[3]);
					auto to = stoi(match[4]);
					auto ys = vector<int>(to - from + 1);
					std::iota(ys.begin(), ys.end(), from);
					result.push_back(Clay(vector<int> { stoi(match[2])}, ys));
				}
				else {
					auto from = stoi(match[3]);
					auto to = stoi(match[4]);
					auto xs = vector<int>(to - from + 1);
					std::iota(xs.begin(), xs.end(), from);
					result.push_back(Clay(xs, vector<int> { stoi(match[2])}));
				}
			}
		}
		return result;
	}
};

TEST_F(day17Fixture, Part1) {
	SetUp("day17_fixture.txt");
	auto actual = Day17::Part1(getTokens());
	EXPECT_EQ(57, actual);
}
