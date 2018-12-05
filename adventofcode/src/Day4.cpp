#include "Day4.h"

#include <algorithm>
#include <numeric>
#include <map>
#include <tuple>

namespace Day4 {
 
	int Part1(std::vector<Record> tokens) {
		std::sort(std::begin(tokens), std::end(tokens));
		std::map<int, std::vector<std::tuple<int, int>>> sleepingSchedule;
		int guard = 0;
		int start, end;
		for (int i = 0; i < tokens.size(); i++) {
			auto inst = tokens[i];
			if (inst.isGuard()) {
				guard = inst.id();
				continue;
			}
			if (inst.sleeps()) {
				sleepingSchedule[guard].push_back(std::make_tuple(inst.getTime(), 0));
			}
			if (inst.awake()) {
				std::tie (start, end) = sleepingSchedule[guard].back();
				sleepingSchedule[guard].pop_back();
				sleepingSchedule[guard].push_back(std::make_tuple(start, inst.getTime()));
			}
		}

		// who sleeps the most?
		int max = 0;
		guard = 0;
		for (auto const &it : sleepingSchedule)
		{
			auto v = sleepingSchedule[it.first];
			auto candidate = std::accumulate(v.begin(), v.end(), 0, [](int acc, std::tuple<int, int> next) {
				int s, e;
				std::tie (s, e) = next;
				acc += (e - s);
				return acc;
			});
			if (candidate > max)
			{
				guard = it.first;
				max = candidate;
			}
		}

		// which minute is the candidate most likely to sleep?
		auto candidate = sleepingSchedule[guard];
		std::map<int, int> minutes;
		for (auto const &it : candidate) {
			std::tie (start, end) = it;
			for (int i = start; i < end; i++) {
				if (minutes.count(i)) {
					minutes[i]++;
				}
				else {
					minutes[i] = 1;
				}
			}
		}
		std::pair<int, int> maximum = *(std::max_element(std::begin(minutes), std::end(minutes), [](std::pair<int, int> p, std::pair<int, int> a) {
			return p.second < a.second;
		}));

		return guard * maximum.first;
	}

	int Part2(std::vector<Record> tokens) {
		std::sort(std::begin(tokens), std::end(tokens));
		std::map<int, std::vector<std::tuple<int, int>>> sleepingSchedule;
		int guard = 0;
		int start, end;
		for (int i = 0; i < tokens.size(); i++) {
			auto inst = tokens[i];
			if (inst.isGuard()) {
				guard = inst.id();
				continue;
			}
			if (inst.sleeps()) {
				sleepingSchedule[guard].push_back(std::make_tuple(inst.getTime(), 0));
			}
			if (inst.awake()) {
				std::tie (start, end) = sleepingSchedule[guard].back();
				sleepingSchedule[guard].pop_back();
				sleepingSchedule[guard].push_back(std::make_tuple(start, inst.getTime()));
			}
		}


		// which minute is the candidate most likely to sleep?
		std::map<int, std::map<int, int>> guardMinutes;
		for (auto const &it : sleepingSchedule) {
			// loop sleeping minutes
			std::map<int, int> minutes;
			for (auto const &sc : it.second) {
				// populate
				std::tie(start, end) = sc;
				for (int i = start; i < end; i++) {
					if (minutes.count(i)) {
						minutes[i]++;
					}
					else {
						minutes[i] = 1;
					}
				}
				guardMinutes[it.first] = minutes;
			}
		}

		
		std::pair<int, int> result { 0, 0 };
		int suspect = 0;
		for (auto const &it : guardMinutes) {
			std::pair<int, int> maximum = *(std::max_element(std::begin(it.second), std::end(it.second), [](std::pair<int, int> p, std::pair<int, int> a) {
				return p.second < a.second;
			}));
			if (maximum.second > result.second) {
				result = maximum;
				suspect = it.first;
			}
		}

		return suspect * result.first;
	}
}