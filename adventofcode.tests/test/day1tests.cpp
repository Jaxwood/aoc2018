#include "pch.h"

#include "Day1.h"


TEST(Day1, Example1) {
	auto actual = Day1::Sum("day1_fixture_1.txt");
	EXPECT_EQ(0, actual);
}

TEST(Day1, Example2) {
	auto actual = Day1::Sum("day1_fixture_2.txt");
	EXPECT_EQ(3, actual);
}

TEST(Day1, Example3) {
	auto actual = Day1::Sum("day1_fixture_3.txt");
	EXPECT_EQ(-6, actual);
}