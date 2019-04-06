#include "Day22.h"

using namespace std;

namespace Day22 {
	map<tuple<int, int>, long long> erosionLevels;

	map<int, ErosionLevel> cavernTypes = {
		{ 0, Rocky },
		{ 1, Wet },
		{ 2, Narrow }
	};

	map<ErosionLevel, set<Tools>> toolsForSurface = {
		{ Rocky, { ClimbingGear, Torch } },
		{ Wet, { ClimbingGear, Neither } },
		{ Narrow, { Torch, Neither } }
	};

	long long Cave::calculateErosionLevel(size_t x, size_t y) {
		int targetX, targetY;
		tie(targetX, targetY) = this->target;
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
			if (erosionLevels[make_tuple(x, y)] != 0) {
				return erosionLevels[make_tuple(x, y)];
			}
			geologicalIndex = calculateErosionLevel(x - 1, y) * calculateErosionLevel(x, y - 1);
		}
		erosionLevels[make_tuple(x, y)] = (geologicalIndex + this->depth) % 20183;
		return erosionLevels[make_tuple(x, y)];
	}

	int Part1(tuple<int, int> target, int depth) {
		auto cave = Cave(depth, target);
		return cave.sum();
	}

	int Cave::sum() {
		int total = 0;
		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j <= 10; j++) {
				total += cavernTypes[this->calculateErosionLevel(i, j) % 3];
			}
		}
		return total;
	}

	vector<tuple<int, int>> Cave::getNeighbors(tuple<int, int> coord)
	{
		vector<tuple<int, int>> result;
		int x, y;
		tie(x, y) = coord;

		result.push_back(make_tuple(x + 1, y));
		result.push_back(make_tuple(x, y + 1));
		if (x > 0) {
			result.push_back(make_tuple(x - 1, y));
		}
		if (y > 0) {
			result.push_back(make_tuple(x, y - 1));
		}
		if (result.empty()) {
			throw exception("no neighbors found");
		}
		return result;
	}

	Tools Cave::switchTool(Tools tool, set<Tools> tools) {
		for (auto &t : tools) {
			if (t != tool) {
				return t;
			}
		}
		throw exception("should not occuor");
	}

	tuple<int, Tools> Cave::getTravelCost(Tools tool, tuple<int, int> from, tuple<int, int> to) {
		int x, y, x1, y1;
		tie(x, y) = from;
		tie(x1, y1) = to;
		auto erosionLevelSource = cavernTypes[(this->calculateErosionLevel(x, y)) % 3];
		auto erosionLevelTarget = cavernTypes[(this->calculateErosionLevel(x1, y1)) % 3];
		if (toolsForSurface[erosionLevelTarget].find(tool) != toolsForSurface[erosionLevelTarget].end()) {
			return make_tuple(1, tool);
		}
		else {
			return make_tuple(8, this->switchTool(tool, toolsForSurface[erosionLevelSource]));
		}
	}

	Cave::Cave(int depth, tuple<int, int> target) {
		this->depth = depth;
		this->target = target;
	}

	typedef tuple<tuple<int, int>, Tools, int> Node;

	int Part2(tuple<int, int> target, int depth) {
		auto cave = Cave(depth, target);
		auto compare = [](const Node &n1, const Node &n2) -> bool {
			int first, second;
			Tools t1, t2;
			tuple<int, int> firstCoord, secondCoord;
			tie(firstCoord, t1, first) = n1;
			tie(secondCoord, t2, second) = n2;
			return first > second;
		};

		map<tuple<tuple<int, int>, Tools>, int> travelCosts;
		priority_queue<Node, vector<Node>, decltype(compare)> queue(compare);
		set<tuple<tuple<int, int>, Tools>> visited;
		queue.push(make_tuple(make_tuple(0, 0), Torch, 0));
		int min = INT32_MAX;

		while (true)
		{
			int currentTravelCost; tuple<int, int> from; Tools tool;
			tie(from, tool, currentTravelCost) = queue.top(); queue.pop();
			visited.insert(make_tuple(from, tool));
			if (from == target) {
				break;
			}
			auto neighbors = cave.getNeighbors(from);
			for (auto &to : neighbors) {
				int moveCost; Tools equipedTool;
				tie(moveCost, equipedTool) = cave.getTravelCost(tool, from, to);
				auto location = make_tuple(to, equipedTool);
				if (visited.find(location) == visited.end()) {
					int totalTravelCost = moveCost + currentTravelCost;
					auto recordedTravelCost = travelCosts[location];
					if (recordedTravelCost == 0) {
						recordedTravelCost = INT32_MAX;
					}
					if (totalTravelCost < recordedTravelCost) {
						queue.push(make_tuple(to, equipedTool, totalTravelCost));
						travelCosts[location] = totalTravelCost;
					}
					if (to == target) {
						auto next = equipedTool == ClimbingGear ? totalTravelCost + 7 : totalTravelCost;
						if (next < min) {
							min = next;
						}
					}
				}
			}
		}
		return min;
	}
}
