#include "pch.h"

#include "Day11.h"
#include <tuple>

TEST(Day11, Part1) {
	auto actual = Day11::Part1(3, 5034);
	EXPECT_EQ(std::make_tuple(235,63), actual);
}
// slow test
TEST(Day11, DISABLED_Part2) {
	auto actual = Day11::Part2(5034);
	EXPECT_EQ(std::make_tuple(229,251,16), actual);
}
