#include "Day2.h"

#include <algorithm>

namespace Day2 {

	int Part1(std::vector<std::string> tokens) {
		int twos = 0;
		int threes = 0;
		bool two = false;
		bool three = false;
		for (auto i = 0; i < tokens.size(); i++) {
			auto candidate = tokens[i];
			two = false;
			three = false;
			for (auto j = 0; j < candidate.size(); j++) {
				auto cnt = std::count(std::begin(candidate), std::end(candidate), candidate[j]);
				if (!two && cnt == 2) {
					twos = twos + 1;
					two = true;
				}
				if (!three && cnt == 3) {
					threes = threes + 1;
					three = true;
				}
				if (two && three) {
					break;
				}
			}
		}

		return twos * threes;
	}

	std::string Part2(std::vector<std::string> tokens) {
		return "";
	}
}
