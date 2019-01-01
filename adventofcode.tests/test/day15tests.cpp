#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>

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

TEST_F(day15Fixture, Part1a) {
	SetUp("day15_example.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(36334, actual);
}

TEST_F(day15Fixture, Part1b) {
	SetUp("day15_example2.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(39514, actual);
}

TEST_F(day15Fixture, Part1c) {
	SetUp("day15_example3.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(27755, actual);
}

TEST_F(day15Fixture, Part1d) {
	SetUp("day15_example4.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(28944, actual);
}

TEST_F(day15Fixture, Part1e) {
	SetUp("day15_example5.txt");
	auto actual = Day15::Part1(getTokens());
	EXPECT_EQ(18740, actual);
}

TEST_F(day15Fixture, atlas_equal) {
	SetUp("day15_atlas.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_swap) {
	SetUp("day15_atlas.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	SetUp("day15_atlas_swap.txt");
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	actual.swap(make_tuple(1,1), make_tuple(1,2));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_neighbors) {
	SetUp("day15_atlas.txt");
	auto sut = Day15::Atlas();
	sut.initialize(getTokens());
	auto actual = sut.neighbors(make_tuple(1,1));
	auto expected = vector<Point>{ make_tuple(1,2), make_tuple(2,1) };
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_clear) {
	SetUp("day15_atlas.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	SetUp("day15_atlas_clear.txt");
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	actual.clear(make_tuple(4,4));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, atlas_types) {
	SetUp("day15_atlas.txt");
	auto sut = Day15::Atlas();
	sut.initialize(getTokens());
	auto actual = sut.types('G');
	sort(begin(actual), end(actual));
	auto expected = vector<Point>{ make_tuple(1,1), make_tuple(1,4), make_tuple(1,7), make_tuple(4,1), make_tuple(4,7), make_tuple(7,1), make_tuple(7,4), make_tuple(7,7) };
	sort(begin(expected), end(expected));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, player_takehit) {
	auto actual = Player(make_tuple(1, 1), true, 3);
	auto target = Player(make_tuple(2, 1), false, 3);
	actual.attack(&target);
	EXPECT_EQ(false, target.alive());
}

TEST_F(day15Fixture, player_outofreach) {
	auto actual = Player(make_tuple(1, 1), true, 2);
	auto target = Player(make_tuple(2, 2), true, 2);
	actual.attack(&target);
	EXPECT_EQ(true, target.alive());
}

TEST_F(day15Fixture, player_sort) {
	auto actual = vector<Player>{ Player(make_tuple(3, 3), true, 2), Player(make_tuple(2,3),  true,2), Player(make_tuple(0,4), true,2) };
	auto expected = vector<Player>{ Player(make_tuple(2, 3), true, 2), Player(make_tuple(3,3),  true,2), Player(make_tuple(0,4), true,2) };
	sort(begin(actual), end(actual));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, pathfinder_move) {
	SetUp("day15_pathfinder_before.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());
	SetUp("day15_pathfinder_after.txt");
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());
	auto sut = Day15::PathFinder(&actual);
	sut.move(make_tuple(2,1));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, pathfinder_target) {
	SetUp("day15_pathfinder_before.txt");
	auto atlas = Day15::Atlas();
	atlas.initialize(getTokens());
	auto sut = Day15::PathFinder(&atlas);
	auto actual = sut.targets(make_tuple(2,1));
	auto expected = vector<Point>{ make_tuple(4,3) };
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, pathfinder_targetinrange) {
	SetUp("day15_pathfinder_before.txt");
	auto atlas = Day15::Atlas();
	atlas.initialize(getTokens());
	auto sut = Day15::PathFinder(&atlas);
	auto actual = sut.targetLocations(vector<Point> { make_tuple(4, 3) });
	auto expected = vector<Point>{ make_tuple(3,3), make_tuple(5,3), make_tuple(4,2) };
	sort(begin(expected), end(expected));
	sort(begin(actual), end(actual));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, pathfinder_reachable) {
	SetUp("day15_pathfinder_reachable.txt");
	auto atlas = Day15::Atlas();
	atlas.initialize(getTokens());
	auto sut = Day15::PathFinder(&atlas);
	auto from = make_tuple(1, 1);
	auto targets = sut.targetLocations(sut.targets(from));
	auto reachable = sut.reachable(from, targets);
	vector<Point> actual;
	transform(begin(reachable), end(reachable), back_inserter(actual), [](pair<Point, int> p) {
		return p.first;
	});

	auto expected = vector<Point>{ make_tuple(1, 3), make_tuple(2, 2), make_tuple(3, 1), make_tuple(3, 3) };
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, pathfinder_shortestPath) {
	SetUp("day15_pathfinder_reachable.txt");
	auto atlas = Day15::Atlas();
	atlas.initialize(getTokens());
	auto sut = Day15::PathFinder(&atlas);
	auto data = map<Point, int>();
	data[make_tuple(1, 1)] = 2;
	data[make_tuple(2, 1)] = 3;
	data[make_tuple(3, 1)] = 2;
	auto actual = sut.shortestPath(data);
	auto expected = vector<Point>{ make_tuple(1,1), make_tuple(3,1) };
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, pathfinder_readingOrder) {
	SetUp("day15_pathfinder_reachable.txt");
	auto atlas = Day15::Atlas();
	atlas.initialize(getTokens());
	auto sut = Day15::PathFinder(&atlas);
	auto data = vector<Point>{ make_tuple(4,2), make_tuple(3,3) };
	auto actual = sut.selectByReadingOrder(data);
	EXPECT_EQ(make_tuple(4,2), actual);
}

TEST_F(day15Fixture, pathfinder_moves) {
	SetUp("day15_pathfinder_initial.txt");
	auto actual = Day15::Atlas();
	actual.initialize(getTokens());

	SetUp("day15_pathfinder_round1.txt");
	auto expected = Day15::Atlas();
	expected.initialize(getTokens());

	auto sut = PathFinder(&actual);

	sut.move(make_tuple(1,1));
	sut.move(make_tuple(4,1));
	sut.move(make_tuple(7,1));
	sut.move(make_tuple(1,4));
	sut.move(make_tuple(4,4));
	sut.move(make_tuple(7,4));
	sut.move(make_tuple(1,7));
	sut.move(make_tuple(4,7));
	sut.move(make_tuple(7,7));
	EXPECT_EQ(expected, actual);
}

TEST_F(day15Fixture, game_over) {
	auto players = vector<Player>{};
	auto sut = Game(players);
	EXPECT_EQ(true, sut.over());
}

TEST_F(day15Fixture, game_notOver) {
	auto players = vector<Player>{ Player(make_tuple(0,0), true, 200),Player(make_tuple(0,0), false, 200) };
	auto sut = Game(players);
	EXPECT_EQ(false, sut.over());
}
