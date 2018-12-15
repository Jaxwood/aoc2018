#include "pch.h"

#include "Day11.h"
#include <tuple>

TEST(Day11, Part1) {
	auto actual = Day11::Part1(3, 5034);
	EXPECT_EQ(std::make_tuple(235,63), actual);
}
TEST(Day11, Part2) {
	auto actual = Day11::Part2(5034);
	EXPECT_EQ(std::make_tuple(235,63, 0), actual);
}
