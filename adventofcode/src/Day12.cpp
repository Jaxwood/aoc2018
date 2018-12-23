#include "Day12.h"

namespace Day12 {
	string currentState;

	int sum(int generations, string state) {
		int sum = 0;
		for (int i = 0; i < state.size(); i++) {
			if (state[i] == '#') {
				sum += i - generations;
			}
		}
		return sum;
	}

	string getCurrentState() {
		return currentState;
	}

	string getPattern(int idx, string state) {
		if (idx == 1) {
			return "." + state.substr(idx - 1, 4);
		}
		if (idx == 0) {
			return ".." + state.substr(idx, 3);
		}
		if (idx == (-1)) {
			return "..." + state.substr(0, 2);
		}
		if (idx == state.size() - 2) {
			return state.substr(idx - 2, 4) + ".";
		}
		if (idx == state.size() - 1) {
			return state.substr(idx - 2, 3) + "..";
		}
		if (idx == state.size()) {
			return state.substr(idx - 2, 2) + "...";
		}
		return state.substr(idx-2, 5);
	}

	int Part1(int generations, string state, unordered_map<string, string> rules) {
		// for each generation
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
				nextState += value;
			}
			currentState = nextState;
			state = nextState;
		}

		return sum(generations, state);
	}
}
