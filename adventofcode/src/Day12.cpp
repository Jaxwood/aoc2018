#include "Day12.h"


namespace Day12 {

	int Part1(string initialState, map<string, string> input) {
		initialState = "..." + initialState + "...";
		int sum = 0;
		int idx = 3;
		for (int g = 0; g < 20; g++) {
			string generation = "";
			for (int i = 2; i < initialState.size() - 2; i++) {
				string pattern = "";
				copy_n(begin(initialState) + i - 2, 5, back_inserter(pattern));
				if (input.find(pattern) != input.end()) {
					generation += input[pattern];
				}
				else {
					generation += '.';
				}
			}
			initialState = "..." + generation + "...";
			idx += 1;
		}
		string positives;
		string negatives;
		copy(begin(initialState) + idx, end(initialState), back_inserter(positives));
		copy(begin(initialState), begin(initialState) + idx + 1, back_inserter(negatives));
		for (int i = 0; i < positives.size(); i++) {
			if (positives[i] == '#') {
				sum += i;
			}
		}
		reverse(begin(negatives), end(negatives));
		for (int i = 0; i <= negatives.size(); i++) {
			if (negatives[i] == '#') {
				sum -= i;
			}
		}
		return sum;
	}
}
