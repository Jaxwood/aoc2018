#include "Day9.h"

#include <numeric>
#include <list>
#include <unordered_map>

using namespace std;

namespace Day9 {
	int nextMablePosition(int mablePosition, int size) {
		return mablePosition == size - 1 ? 1 : (mablePosition += 2);
	}
	long long Part1(int participants, int lastMable) {
		// setup game
		int mablePosition = 1;
		list<int> game = { 0, 1 };
		auto it = begin(game);
		int player = 2;
		unordered_map<int, long long> players;
		int size = 2;
		// turns
		for (int i = 2; i <= lastMable; i++) {
			if (i % 23 == 0) {
				if (mablePosition > 7) {
					mablePosition -= 7;
					for (int j = 0; j < 8; j++) {
						it = prev(it);
					}
				}
				else {
					mablePosition = size - (7 - mablePosition);
					it = begin(game);
					for (int j = 0; j < mablePosition; j++) {
						it = next(it);
					}
				}
				players[player] += i + *it;
				it = next(game.erase(it));
				size--;
			}
			else {
				// are we at the end?
				mablePosition = nextMablePosition(mablePosition, size);
				if (mablePosition == 1) {
					it = next(begin(game));
				}
				else {
					it = next(it);
				}
				it = next(game.insert(it, i));
				size++;
			}

			// update active player
			player = player == participants ? 1 : (player += 1);
		}
		long long highscore = 0;
		for (auto &p : players) {
			if (p.second > highscore) {
				highscore = p.second;
			}
		}

		return highscore;
	}

	long long Part2(int players, int lastMable) {
		return Part1(players, lastMable * 100);
	}
}
