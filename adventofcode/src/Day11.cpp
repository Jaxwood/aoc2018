#include "Day11.h"

#include <numeric>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

namespace Day11 {

	int hundredDigit(int num) {
		vector<int> digits;
		while (num >= 10) {
			digits.push_back(num % 10);
			num = num / 10;
		}
		digits.push_back(num);
		if (digits.size() < 3) {
			num = 0;
		}
		else {
			num = digits[2];
		}
		return num;
	}

	int calculatePowerLevel(int x, int y, int serialNumber) {
		auto rackId = x + 10;
		int powerlevel = (rackId * y) + serialNumber;
		powerlevel = powerlevel * rackId; 
		return hundredDigit(powerlevel) - 5;
	}

	vector<tuple<int, int>> getCoords(int x, int y, int sizeX, int sizeY) {
		vector<tuple<int, int>> result;
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				result.push_back(make_tuple(x+i, y+j));
			}
		}
		return result;
	}

	int calculateTotalPowers(vector<tuple<int, int>> coords, int serialNumber) {
		int x, y;
		int total = 0;
		for (int i = 0; i < coords.size(); i++) {
			tie(x, y) = coords[i];
			total += calculatePowerLevel(x, y, serialNumber);
		}
		return total;
	}

	tuple<int, int> Part1(int sizeX, int sizeY, int serialNumber) {
		map<tuple<int, int>, int> totals;
		// loop x
		for (int i = 1; i <= 300 - sizeX; i++) {
			// loop y
			for (int j = 1; j <= 300 - sizeY; j++) {
				auto coords = getCoords(i, j, sizeX, sizeY);
				totals[make_tuple(i,j)] = calculateTotalPowers(coords, serialNumber);
			}
		}
		int best = 0;
		tuple<int, int> candidate;
		for (auto &t : totals) {
			if (t.second > best) {
				best = t.second;
				candidate = t.first;
			}
		}
		return candidate;
	}

}
