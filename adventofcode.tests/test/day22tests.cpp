#include "pch.h"

#include <tuple>

#include "Day22.h"

using namespace std;
using namespace Day22;

TEST(day22Fixture, Part1) {
	auto actual = Day22::Part1(make_tuple(10,10), 510);
	EXPECT_EQ(114, actual);
}

TEST(day22Fixture, Part2) {
	auto actual = Day22::Part2(make_tuple(10,10), 510);
	EXPECT_EQ(45, actual);
}

TEST(day22Fixture, Part2A) {
	auto actual = Day22::Part2(make_tuple(14,709), 6084);
	EXPECT_EQ(987, actual); // 989
}
