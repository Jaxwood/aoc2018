#include "Day2.h"

#include <algorithm>
#include <numeric>
#include <iterator>

namespace Day2 {

	bool matches(int num, std::string candidate) {
		for (auto j = 0; j < candidate.size(); j++) {
			auto cnt = std::count(std::begin(candidate), std::end(candidate), candidate[j]);
			if (cnt == num) {
				return true;
			}
		}

		return false;
	}

	std::vector<std::string> getCandidates(std::vector<std::string> tokens) {

		std::vector<std::string> candidates;
		auto it = std::back_inserter(candidates); 
		std::copy_if(std::begin(tokens), std::end(tokens), it, [](std::string token){
			return matches(2, token) || matches(3, token);
		});

		return candidates;
	}

	int Part1(std::vector<std::string> tokens) {
		auto candidates = getCandidates(tokens);

		auto twos = std::count_if(std::begin(candidates), std::end(candidates), [](std::string candidate) { return matches(2, candidate); });
		auto threes = std::count_if(std::begin(candidates), std::end(candidates), [](std::string candidate) { return matches(3, candidate); });

		return twos * threes;
	}

	bool hasOneDifference(std::string toMatch, std::string candidate) {
		// get the first difference
		auto pair = std::mismatch(std::begin(toMatch), std::end(toMatch), std::begin(candidate));
		// check if rest is equal
		return std::equal(pair.first + 1, std::end(toMatch), pair.second + 1);
	}

	std::pair<std::string, std::string> getLetters(std::vector<std::string> candidates) {
		for (auto i = 0; i < candidates.size() - 1; i++) {
			auto candidate = candidates[i];
			// compare with other candidates
			for (auto j = i+1; j < candidates.size(); j++) {
				auto surrogate = candidates[j];
				if (hasOneDifference(candidate, surrogate)) {
					return std::make_pair(candidate, surrogate);
				}
			}
		}

		return std::make_pair("", "");
	}

	std::string merge(std::string first, std::string last) {
		std::string result = "";
		for (auto i = 0; i < first.size(); i++) {
			if (first[i] == last[i]) {
				result += first[i];
			}
		}
		return result;
	}

	std::string Part2(std::vector<std::string> tokens) {

		auto candidates = getCandidates(tokens);
		auto letters = getLetters(candidates);

		return merge(letters.first, letters.second);
	}
}