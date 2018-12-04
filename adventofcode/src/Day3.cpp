#include "Day3.h"

namespace Day3 {

	int Part1(std::vector<Fabric> tokens) {

		auto arr = new int[8][8];
		int overlaps = 0;
		for (int i = 0; i < tokens.size(); i++) {
			auto tk = tokens[i];
			for (int j = tk.left(); j < tk.right(); j++) {
				for (int k = tk.top(); k < tk.bottom(); k++) {
					if (arr[j][k] < 0) {
						arr[j][k] = 0;
					}
					arr[j][k]++;
					if (arr[j][k] == 2) {
						overlaps++;
					}
				}
			}
		}
		delete[] arr;
		return overlaps;
	}

	int Part2(std::vector<Fabric> tokens) {

		auto arr = new int[8][8];
		int overlaps = 0;
		for (int i = 0; i < tokens.size(); i++) {
			auto tk = tokens[i];
			for (int j = tk.left(); j < tk.right(); j++) {
				for (int k = tk.top(); k < tk.bottom(); k++) {
					if (arr[j][k] < 0) {
						arr[j][k] = 0;
					}
					arr[j][k]++;
					if (arr[j][k] == 2) {
						overlaps++;
					}
				}
			}
		}

		// check for overlaps
		for (int i = 0; i < tokens.size(); i++) {
			bool found = true;
			auto tk = tokens[i];
			for (int j = tk.left(); j < tk.right(); j++) {
				for (int k = tk.top(); k < tk.bottom(); k++) {
					if (arr[j][k] > 1) {
						found = false;
						break;
					}
				}
				if (!found) {
					break;
				}
			}
			if (found) {
				return tk.id();
			}
		}

		delete[] arr;
		return 0;
	}
}