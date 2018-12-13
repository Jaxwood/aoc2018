#include "Day9.h"

#include <map>
#include <vector>

using namespace std;

namespace Day9 {

	int scorePosition(int position, int size) {
		if (position - 7 < 0) {
			return size - position - 7;
		}
		else {
			return position - 7;
		}
	}

	int Part1(int participants, int lastMable) {
		// setup game
		map<int, int> score;
		size_t player = 1;
		int position = 0;
		vector<int> mables;
		mables.push_back(0);

		for (size_t i = 1; i < lastMable; i++) {
			auto size = mables.size();
			// update score
			if (i % 23 == 0) {
				position = scorePosition(position, size);
				score[player] = i;
				score[player] += mables.at(position);
				mables.erase(begin(mables) + position);
			}

			// update position
			mables.push_back(i);

			if (position + 2 >= size) {
				position = 1;
			}
			else {
				position += 2;
			}

			// next turn
			if (player == participants) {
				player = 1;
			}
			else {
				player++;
			}
		}

		// get the highest score
		int total = 0;
		for (auto &p : score) {
			if (p.second > total) {
				total = p.second;
			}
		}
		return total;
	}

	int Part2(int players, int lastMable) {
		return Part1(players, lastMable * 100);
	}
}
