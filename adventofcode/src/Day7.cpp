#include "Day7.h"

using namespace std;

namespace Day7 {

	// check if requirements are fulfilled
	bool valid(vector<string> requirements, vector<string> fulfilled) {
		for (auto r : requirements) {
			if (count(begin(fulfilled), end(fulfilled), r) == 0) {
				return false;
			}
		}
		return true;
	}

	// choice based on alphabetical order
	string bestChoice(vector<string> choices) {
		sort(begin(choices), end(choices));
		return choices[0];
	}

	// do not add already added steps
	bool canBeAdded(string n, vector<string> result) {
		return count(begin(result), end(result), n) == 0;
	}

	vector<string> noRequirements(map<string, vector<string>> required, map<string, vector<string>> next) {
		vector<string> result;
		for (auto nxt : next) {
			if (required.count(nxt.first) == 0) {
					result.push_back(nxt.first);
			}
		}
		return result;
	}

	// calculate the next step
	vector<string> nextStep(map<string, vector<string>> required, map<string, vector<string>> next, vector<string> result, int length)
	{
		if (result.size() == length) return result;

		vector<string> choice;
		for (auto res : result) {
			for (auto n : next[res]) {
				if (valid(required[n], result)) {
					if (canBeAdded(n, result)) {
						choice.push_back(n);
					}
				}
			}
		}
		// add the steps that does not have any requirements
		auto noReq = noRequirements(required, next);
		for (auto r : noReq) {
			if (canBeAdded(r, result)) {
				choice.push_back(r);
			}
		}
		// find the best match
		result.push_back(bestChoice(choice));
		return nextStep(required, next, result, length);
	}

	int uniques(map<string, vector<string>> required, map<string, vector<string>> next) {
		set<string> letters;
		for (auto n : next) {
			letters.insert(n.first);
		}
		for (auto n : required) {
			letters.insert(n.first);
		}
		return letters.size();
	}

	string Part1(vector<tuple<string, string>> tokens) {
		string from, to;
		map<string, vector<string>> required, next;

		// find traversal and requirements
		for (auto token : tokens) {
			tie(from, to) = token;
			required[to].push_back(from);
			next[from].push_back(to);
		}

		// get the root
		auto result = noRequirements(required, next);

		auto start = bestChoice(result);
		result.clear();
		result.push_back(start);

		result = nextStep(required, next, result, uniques(required, next));
		string token = "";
		for (auto r : result) {
			token += r;
		}

		return token;
	}

	int Part2(vector<tuple<string, string>> tokens, int elves) {
		WorkerPool pool = WorkerPool(tokens, elves);
		Sleigh sleigh = Sleigh(tokens);
		while (sleigh.moreMoves())
		{
			auto moves = sleigh.move();
			auto accepted = pool.assignWork(moves);
			for(auto &accept : accepted) {
				sleigh.accept(accept);
			}
			pool.tick();
		}
		pool.wait();
		return pool.time();
	}
}
