#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>

#include "Day15.h"

using namespace std;
using namespace Day15;

class day15Fixture : public ::testing::Test {

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

TEST_F(day15Fixture, Part1) {
	SetUp("day15_fixture.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(27730, actual);
}

TEST_F(day15Fixture, atlas_equal) {
	SetUp("day15_fixture.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_swap) {
	SetUp("day15_fixture.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	SetUp("day15_atlas_swap.txt");
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	actual.swap(make_tuple(1,1), make_tuple(1,2));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_neighbors) {
	SetUp("day15_fixture.txt");
	auto sut = Day15::Atlas();
	sut.initialize(getTokens());
	auto actual = sut.neighbors(make_tuple(1,1));
	auto expected = vector<Point>{ make_tuple(2,1), make_tuple(2,1) };
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_clear) {
	SetUp("day15_fixture.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	SetUp("day15_atlas_clear.txt");
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	actual.clear(make_tuple(4,4));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_types) {
	SetUp("day15_fixture.txt");
	auto sut = Day15::Atlas();
	sut.initialize(getTokens());
	auto actual = sut.types('G');
	sort(begin(actual), end(actual));
	auto expected = vector<Point>{ make_tuple(1,1), make_tuple(1,4), make_tuple(1,7), make_tuple(4,1), make_tuple(4,7), make_tuple(7,1), make_tuple(7,4), make_tuple(7,7) };
	sort(begin(expected), end(expected));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, player_takehit) {
	auto actual = Player(make_tuple(1, 1), 3);
	auto target = Player(make_tuple(2, 1), 3);
	actual.attack(&target);
	EXPECT_EQ(false, target.alive());
}

TEST_F(day15Fixture, player_outofreach) {
	auto actual = Player(make_tuple(1, 1), 2);
	auto target = Player(make_tuple(2, 2), 2);
	actual.attack(&target);
	EXPECT_EQ(true, target.alive());
}

TEST_F(day15Fixture, player_sort) {
	auto actual = vector<Player>{ Player(make_tuple(3, 3), 2), Player(make_tuple(2,3), 2), Player(make_tuple(0,4),2) };
	auto expected = vector<Player>{ Player(make_tuple(2, 3), 2), Player(make_tuple(3,3), 2), Player(make_tuple(0,4),2) };
	sort(begin(actual), end(actual));
	EXPECT_EQ(expected, actual);
}
