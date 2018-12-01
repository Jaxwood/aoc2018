#include "pch.h"

#include "Day1.h"


TEST(Day1, Solution1) {
	auto actual = Day1::Sum("day1_fixture.txt");
	EXPECT_EQ(0, actual);
}