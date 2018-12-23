#include "Day12.h"

namespace Day12 {
	string currentState;
	int startIdx;

	int sum(int generations, string state) {
		int sum = 0;
		for (int i = 0; i < state.size(); i++) {
			if (state[i] == '#') {
				sum += generations + i;
			}
		}
		return sum;
	}

	string getCurrentState() {
		return currentState;
	}

	int getStartIdx() {
		return startIdx;
	}

	string getPattern(int idx, string state) {
		if (idx < 2) {
			return string(2 - idx, '.') + state.substr(0, 3 + idx);
		}
		auto size = state.size();
		if (idx > size - 3) {
			return state.substr(idx - 2, size - idx + 2) + string(3 - (size - idx), '.');
		}
		return state.substr(idx-2, 5);
	}

	string& rtrim(string& str)
	{
		str.erase(str.find_last_not_of('.') + 1);
		return str;
	}

	string& ltrim(string& str)
	{
		int cnt = str.find_first_not_of('.');
		startIdx += cnt;
		str.erase(0, cnt);
		return str;
	}

	int Part1(int generations, string state, unordered_map<string, string> rules) {
		// for each generation
		startIdx = 0;
		for (int i = 0; i < generations; i++) {
			string nextState = "";
			// generate next generation
			for (int j = 0; j < state.size()+2; j++) {
				string value = ".";
				string pattern = getPattern(j-1, state);
				if (rules.find(pattern) != end(rules)) {
					// match rule
					value = rules[pattern];
				}
				if (j == 0 && value == ".") {
					// do nothing
				}
				else {
					if (j == 0) {
						startIdx--;
					}
					nextState += value;
				}
			}

			currentState = ltrim(rtrim(nextState));
			state = nextState;
		}

		return sum(startIdx, state);
	}
}
