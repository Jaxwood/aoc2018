#include "pch.h"

#include "Day11.h"
#include <tuple>

TEST(Day11, Part1a) {
	auto actual = Day11::Part1(3, 3, 5034);
	EXPECT_EQ(std::make_tuple(235,63), actual);
}
