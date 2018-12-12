#include "Day9.h"

#include <numeric>
#include <vector>
#include <map>

using namespace std;

namespace Day9 {
	int Part1(int participants, int lastMable) {
		// setup game
		int currentMable = 0;
		vector<int> game;
		game.push_back(0);
		int player = 1;
		map<int, int> players;

		// turns
		for (int i = 1; i <= lastMable; i++) {
			if (i % 23 == 0) {
				players[player] += i;
				if (currentMable > 7) {
					currentMable -= 7;
				}
				else {
					int diff = 7 - currentMable;
					currentMable = game.size() - diff;
				}
				players[player] += game.at(currentMable);
				game.erase(begin(game) + currentMable);
			}
			else {
				if (i == 1) {
					game.push_back(i);
					currentMable = i;
				}
				// are we at the end?
				else if (currentMable == game.size() - 1) {
					currentMable = 1;
					game.insert(begin(game) + currentMable, currentMable, i);
				}
				else {
					currentMable += 2;
					game.insert(begin(game) + currentMable, 1, i);
				}
			}

			// update active player
			if (player == participants) {
				player = 1;
			}
			else {
				++player;
			}
		}
		int highscore = 0;
		for (auto &p : players) {
			if (p.second > highscore) {
				highscore = p.second;
			}
		}

		return highscore;
	}

	int Part2(int players, int lastMable) {
		return Part1(players, lastMable * 100);
	}
}
