#include "Day6.h"

#include <algorithm>
#include <tuple>
#include <map>
#include <iterator>

namespace Day6 {

	std::tuple<bool, Coord> getDistance(std::vector<Coord> coords, int x, int y) {
		std::map<Coord, int> distances;
		for (int i = 0; i < coords.size(); i++) {
			auto candidate = coords[i];
			distances[candidate] = abs(candidate.getX() - x) + abs(candidate.getY() - y);
		}

		// find the lowest value
		int lowest = INT_MAX;
		Coord result;
		for (auto &kv : distances) {
			if (kv.second < lowest) {
				lowest = kv.second;
				result = kv.first;
			}
		}

		// count matches
		int cnt = 0;
		for (auto &kv : distances) {
			if (kv.second == lowest) {
				cnt++;
			}
		}

		return std::make_tuple<bool, Coord>(cnt == 1, (Coord)result);
	}

	int getFinite(std::vector<Coord> coords) {

		auto it = std::max_element(std::begin(coords), std::end(coords), [](Coord a, Coord b) {
			return (a.getX() + a.getY()) < (b.getX() + b.getY());
		});

		// initialize
		std::map<Coord, int> closest;
		for (int i = 0; i < coords.size(); i++) {
			closest[coords[i]] = 0;
		}

		// loop coordinates
		bool result = false;
		Coord candidate;
		for (int x = 0; x <= it->getX(); x++) {
			for (int y = 0; y <= it->getY(); y++) {
				// find closest
				std::tie (result, candidate) = getDistance(coords, x, y);
				if (result) {
					closest[candidate]++;
				}
			}
		}

		int max = INT_MIN;
		for (auto &c : closest) {
			if (c.second > max) {
				max = c.second;
			}
		}
		return max;
	}

	int Part1(std::vector<Coord> coords) {
		return getFinite(coords);
	}
}
