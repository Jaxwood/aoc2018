#include "pch.h"

#include "Day1.h"


TEST(Day1, Example1) {
	auto actual = Day1::Part1("day1_fixture_1.txt");
	EXPECT_EQ(0, actual);
}

TEST(Day1, Example2) {
	auto actual = Day1::Part1("day1_fixture_2.txt");
	EXPECT_EQ(3, actual);
}

TEST(Day1, Example3) {
	auto actual = Day1::Part1("day1_fixture_3.txt");
	EXPECT_EQ(-6, actual);
}

TEST(Day1, Part2_Example1) {
	auto actual = Day1::Part2("day1_part2_1.txt");
	EXPECT_EQ(0, actual);
}

TEST(Day1, Part2_Example2) {
	auto actual = Day1::Part2("day1_part2_2.txt");
	EXPECT_EQ(10, actual);
}

TEST(Day1, Part2_Example3) {
	auto actual = Day1::Part2("day1_part2_3.txt");
	EXPECT_EQ(5, actual);
}

TEST(Day1, Part2_Example4) {
	auto actual = Day1::Part2("day1_part2_4.txt");
	EXPECT_EQ(14, actual);
}