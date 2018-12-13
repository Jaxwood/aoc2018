#include "Day9.h"

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

namespace Day9 {

	int getNextPosition(int position, int size)
	{
		// are we at the end?
		if (position == size - 1) {
			position = 1;
		}
		else {
			position += 2;
		}
		return position;
	}

	int getScoringPosition(int position, int size) {
		if (position > 7) {
			position -= 7;
		}
		else {
			int diff = 7 - position;
			position = size - diff;
		}
		return position;
	}

	int Part1(int participants, int lastMable) {
		// setup game
		map<int, int> players;
		vector<int> score;
		score.push_back(0);
		score.push_back(1);
		int position = 0;
		int playerTurn = 2;

		// turns
		for (int i = 2; i <= lastMable; i++) {
			auto size = score.size();

			// is it a scoring turn?
			if (i % 23 == 0) {
				position = getScoringPosition(position, size);
				players[playerTurn] += i;
				players[playerTurn] += score.at(position);
				score.erase(begin(score) + position);
			}
			else {
				position = getNextPosition(position, size);
				score.insert(begin(score) + position, 1, i);
			}

			// update active player
			if (playerTurn == participants) {
				playerTurn = 1;
			}
			else {
				++playerTurn;
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
