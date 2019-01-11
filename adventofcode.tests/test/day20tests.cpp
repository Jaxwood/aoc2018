#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <regex>

#include "Day20.h"

using namespace std;
using namespace Day20;

class day20Fixture : public ::testing::Test {

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

TEST_F(day20Fixture, Part1a) {
	auto actual = Day20::Part1("^ENNWSWW(NEWS|)$");
	EXPECT_EQ(3, actual);
}

TEST_F(day20Fixture, GroupA) {
	auto actual = Day20::group("(NEWS|)ABD");
	EXPECT_EQ("(NEWS|)", actual);
}

TEST_F(day20Fixture, GroupB) {
	auto actual = Day20::group("(NEWS(W|S)W)SS");
	EXPECT_EQ("(NEWS(W|S)W)", actual);
}

TEST_F(day20Fixture, SplitA) {
	auto actual = Day20::split("(W|S)");
	auto expected = vector<string>{ "W", "S" };
	EXPECT_EQ(expected, actual);
}

TEST_F(day20Fixture, SplitB) {
	auto actual = Day20::split("(W|(S|W))");
	auto expected = vector<string>{ "W", "(S|W)" };
	EXPECT_EQ(expected, actual);
}

TEST_F(day20Fixture, SplitC) {
	auto actual = Day20::split("(E|NNENN(EESS(WNSE|)SSS|WWWSSSSE(SW|NNNE)))");
	auto expected = vector<string>{ "E", "NNENN(EESS(WNSE|)SSS|WWWSSSSE(SW|NNNE))" };
	EXPECT_EQ(expected, actual);
}
