#include "Day6.h"

#include <algorithm>
#include <tuple>
#include <map>
#include <set>
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

		// get size of grid
		int maxX = 0;
		int maxY = 0;
		for (int i = 0; i < coords.size(); i++) {
			auto next = coords[i];
			if (next.getX() > maxX) {
				maxX = next.getX();
			}
			if (next.getY() > maxY) {
				maxY = next.getY();
			}
		}

		// initialize
		std::map<Coord, int> closest;
		for (int i = 0; i < coords.size(); i++) {
			closest[coords[i]] = 0;
		}

		// exclude infinites
		bool result = false;
		Coord candidate;
		std::set<Coord> excluded;
		for (int x = 0; x < maxX; x++) {
				std::tie (result, candidate) = getDistance(coords, x, 0);
				if (result) {
					excluded.insert(candidate);
				}
		}
		for (int x = 0; x < maxX; x++) {
				std::tie (result, candidate) = getDistance(coords, x, maxY);
				if (result) {
					excluded.insert(candidate);
				}
		}
		for (int y = 0; y < maxY; y++) {
				std::tie (result, candidate) = getDistance(coords, 0, y);
				if (result) {
					excluded.insert(candidate);
				}
		}
		for (int y = 0; y < maxY; y++) {
				std::tie (result, candidate) = getDistance(coords, maxX, y);
				if (result) {
					excluded.insert(candidate);
				}
		}

		// find the finites
		std::vector<Coord> finites;
		for (auto &inf : coords) {
			if (excluded.count(inf) == 0) {
				finites.push_back(inf);
			}
		}

		// loop coordinates
		for (int x = 0; x <= maxX; x++) {
			for (int y = 0; y <= maxY; y++) {
				// find closest
				std::tie (result, candidate) = getDistance(coords, x, y);
				if (result) {
					closest[candidate]++;
				}
			}
		}

		int max = INT_MIN;
		for (auto &c : closest) {
			if (excluded.count(c.first) == 0)
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
