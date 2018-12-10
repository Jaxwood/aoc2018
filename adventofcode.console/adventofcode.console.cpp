// adventofcode.console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <tuple>

#include "Day10.h"

using namespace Day10;

class day10Fixture {

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

	vector<Point> getTokens() {
		vector<Point> records;
		auto reg = regex("position=<([-|\\s]?\\d+), ([-|\\s]?\\d+)> velocity=<([-|\\s]?\\d+), ([-|\\s]?\\d+)>", regex_constants::ECMAScript);
		for (int i = 0; i < this->_tokens.size(); i++) {
			smatch match;
			if (regex_match(this->_tokens[i], match, reg)) {
				records.push_back(Point(stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])));
			}
		}
		return records;
	}
};

int main()
{
	auto fixture = day10Fixture();
	fixture.SetUp("day10_fixture.txt");
	auto result = Day10::Part1(fixture.getTokens(), 3);
	for (auto &res : result) {
    std::cout << res << endl; 
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
