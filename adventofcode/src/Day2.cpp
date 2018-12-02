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
		std::vector<std::string> candidates;
		for (auto i = 0; i < tokens.size(); i++) {
			auto candidate = tokens[i];
			for (auto j = 0; j < candidate.size(); j++) {
				auto cnt = std::count(std::begin(candidate), std::end(candidate), candidate[j]);
				if (cnt == 2 || cnt == 3) {
					candidates.push_back(candidate);
					break;
				}
			}
		}

		auto diff = 0;
		std::string candidate;
		std::string surrogate;
		for (auto i = 0; i < candidates.size() - 1; i++) {
			if (diff == 1) {
				break;
			}
			candidate = candidates[i];
			// compare with other candidates
			for (auto j = i+1; j < candidates.size(); j++) {
				diff = 0;
				surrogate = candidates[j];
				// compare strings
				for (auto k = 0; k < surrogate.size(); k++) {
					if (candidate[k] != surrogate[k]) {
						diff++;
					}
				}
				if (diff == 1) {
					break;
				}
			}
		}

		std::string result = "";
		for (auto i = 0; i < candidate.size(); i++) {
			if (candidate[i] == surrogate[i]) {
				result += candidate[i];
			}
		}
		return result;
	}
}