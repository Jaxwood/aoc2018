#include "Day22.h"

using namespace std;

namespace Day22 {
	int maxX = 20;
	int maxY = 20;
	map<tuple<int, int>, long long> erosionLevels;

	map<int, ErosionLevel> cavernTypes = {
		{ 0, Rocky },
		{ 1, Wet },
		{ 2, Narrow }
	};

	map<ErosionLevel, vector<Tools>> toolsForSurface = {
		{ Rocky, { ClimbingGear, Torch } },
		{ Wet, { ClimbingGear, Neither } },
		{ Narrow, { Torch, Neither } }
	};

	long long CalculateErosionLevel(tuple<int, int> target, int depth, size_t x, size_t y) {
		int targetX, targetY;
		tie(targetX, targetY) = target;
		long long geologicalIndex;
		if (x == 0 && y == 0) {
			geologicalIndex = 0;
		}
		else if (x == targetX && y == targetY) {
			geologicalIndex = 0;
		}
		else if (x == 0) {
			geologicalIndex = y * 48271;
		}
		else if (y == 0) {
			geologicalIndex = x * 16807;
		}
		else {
			geologicalIndex = erosionLevels[make_tuple(x - 1, y)] * erosionLevels[make_tuple(x, y - 1)];
		}

		erosionLevels[make_tuple(x, y)] = (geologicalIndex + depth) % 20183;
		return erosionLevels[make_tuple(x, y)];
	}

	int Part1(tuple<int, int> target, int depth) {
		int sum = 0;
		ErosionLevel cavern[11][11];
		for (size_t x = 0; x <= 10; x++) {
			for (size_t y = 0; y <= 10; y++) {
				auto erosionLevel = CalculateErosionLevel(target, depth, x, y);
				cavern[y][x] = cavernTypes[erosionLevel % 3];
				sum += (int)cavern[y][x];
			}
		}

		return sum;
	}

	vector<tuple<int, int>> getNeighbors(tuple<int, int> coord)
	{
		vector<tuple<int, int>> result;
		int x, y;
		tie(x, y) = coord;

		if (x + 1 <= maxX) {
			result.push_back(make_tuple(x + 1, y));
		}
		if (x - 1 >= 0) {
			result.push_back(make_tuple(x - 1, y));
		}
		if (y + 1 <= maxY) {
			result.push_back(make_tuple(x, y + 1));
		}
		if (y - 1 >= 0) {
			result.push_back(make_tuple(x, y - 1));
		}
		return result;
	}

	Tools switchTool(Tools tool, vector<Tools> tools) {
		for (auto &t : tools) {
			if (t == tool) {
				continue;
			}
			return t;
		}
	}

	bool canUseTool(ErosionLevel erosionLevel, Tools tool) {
		for (auto &t : toolsForSurface[erosionLevel]) {
			if (tool == t) return true;
		}
		return false;
	}

	int getTravelCost(Tools tool, ErosionLevel erosionLevelSource, ErosionLevel erosionLevelTarget) {
		return canUseTool(erosionLevelTarget, tool) ? 1 : 8;
	}

	tuple<int, int> findNext(set<tuple<int, int>> &visited, map<tuple<int, int>, int> &travelCosts) {
		vector<pair<tuple<int, int>, int>> pairs;
		copy(begin(travelCosts), end(travelCosts), back_inserter(pairs));
		sort(begin(pairs), end(pairs), [](const pair<tuple<int, int>, int> p1, const pair<tuple<int, int>, int> p2) {
			return p1.second < p2.second;
		});
		for (auto &p : pairs) {
			if (visited.find(p.first) == visited.end()) {
				return p.first;
			}
		}
	}

	int Part2(tuple<int, int> target, int depth) {
		ErosionLevel cavern[21][21];
		set<tuple<int, int>> regions;
		map<tuple<int, int>, int> travelCosts;
		for (size_t x = 0; x <= maxX; x++) {
			for (size_t y = 0; y <= maxY; y++) {
				auto erosionLevel = CalculateErosionLevel(target, depth, x, y);
				cavern[y][x] = cavernTypes[erosionLevel % 3];
				regions.insert(make_tuple(x, y));
				travelCosts[make_tuple(x, y)] = INT32_MAX;
			}
		}
		travelCosts[make_tuple(0, 0)] = 0;
		set<tuple<int, int>> visited;
		map<tuple<int, int>, set<Tools>> equipmentList;
		equipmentList[make_tuple(0, 0)] = { Torch };
		int x1, y1, x2, y2;

		while (!regions.empty())
		{
			auto next = findNext(visited, travelCosts);
			regions.erase(next);
			auto neighbors = getNeighbors(next);
			auto equipments = equipmentList[next];
			tie(x1, y1) = next;
			for (auto &neighbor : neighbors) {
				if (visited.find(neighbor) == visited.end()) {
					tie(x2, y2) = neighbor;
					for (auto equipment : equipments) {
						auto cost = getTravelCost(equipment, cavern[y1][x1], cavern[y2][x2]);
						auto newCost = travelCosts[next] + cost;
						if (neighbor == target && equipment == ClimbingGear) {
							newCost += 7;
						}
						if (newCost == travelCosts[neighbor]) {
							equipmentList[neighbor].insert(canUseTool(cavern[y2][x2], equipment) ? equipment : switchTool(equipment, toolsForSurface[cavern[y1][x1]]));
						}
						if (newCost < travelCosts[neighbor]) {
							travelCosts[neighbor] = newCost;
							equipmentList[neighbor] = { canUseTool(cavern[y2][x2], equipment) ? equipment : switchTool(equipment, toolsForSurface[cavern[y1][x1]]) };
						}
					}
				}
			}
			visited.insert(next);
		}

		return travelCosts[target];
	}
}
