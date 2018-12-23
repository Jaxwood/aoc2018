#pragma once

#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>

using namespace std;

namespace Day12 {
	int Part1(int generations, string initialState, unordered_map<string, string> input);
	string getPattern(int idx, string state);
	string getCurrentState();
}
