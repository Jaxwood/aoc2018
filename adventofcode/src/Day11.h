#pragma once

#include <numeric>
#include <vector>
#include <tuple>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

namespace Day11 {
	class Grid {
	private:
		int serialNumber;

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

		int calculatePowerLevel(int x, int y) {
			auto rackId = x + 10;
			int powerlevel = (rackId * y) + this->serialNumber;
			powerlevel = powerlevel * rackId;
			auto result = hundredDigit(powerlevel) - 5;
			return result;
		}

		int getCoords(int x, int y, int size) {
			int result = 0;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					result += calculatePowerLevel(x + i, y + j);
				}
			}
			return result;
		}

	public:
		Grid(int serialNumber) {
			this->serialNumber = serialNumber;
		}

		int totals(int x, int y, int size) {
			return this->getCoords(x, y, size);
		}
	};

	std::tuple<int, int> Part1(int size, int serialNumber);

	std::tuple<int, int, int> Part2(int serialNumber);
}
