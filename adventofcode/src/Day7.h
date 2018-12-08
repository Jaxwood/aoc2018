#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

namespace Day7 {

	class WorkerPool {
	private:
		int workerCount;
		int seconds;
		map<string, int> jobs;
		map<string, int> timetable;
		map<string, vector<string>> requirements;
		string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		bool spareCapacity() {
			auto workingjobs = count_if(begin(this->jobs), end(this->jobs), [](pair<string, int> job) {
				return job.second > 0;
			});
			return workingjobs < this->workerCount;
		}

		bool canBeWorkedOn(string job) {
			bool canWork = true;
			for (auto &requirement : this->requirements[job])
			{
				if (this->jobs[requirement] > 0) {
					return false;
				}
			}
			return true;
		}

		bool hasRunningJobs() {
			return count_if(begin(this->jobs), end(this->jobs), [](pair<string, int> job) {
				return job.second;
			}) > 0;
		}

	public:
		WorkerPool(vector<tuple<string, string>> tokens, int workerCount) {
			string from, to;
			this->workerCount = workerCount;
			this->seconds = 0;
			this->jobs = jobs;
			for (int i = 0; i < letters.size(); i++) {
				timetable[string(1, letters[i])] = i + 1;
			}
			set<string> unique;
			for (auto &token : tokens) {
				tie(from, to) = token;
				this->requirements[to].push_back(from);
			}
		}

		vector<string> assignWork(vector<string> letters) {
			vector<string> acceptedJobs;
			for (auto &letter : letters) {
				if (spareCapacity() && canBeWorkedOn(letter)) {
					this->jobs[letter] = this->timetable[letter];
					acceptedJobs.push_back(letter);
				}
			}
			return acceptedJobs;
		}

		void tick() {
			this->seconds++;
			for(auto &job : this->jobs) {
				if (job.second > 0) {
					job.second--;
				}
			};
		}

		int time() {
			return this->seconds;
		}
		void wait() {
			while (hasRunningJobs()) {
				tick();
			}
		}
	};

	class Sleigh {
	private:

		vector<tuple<string, string>> tokens;
		map<string, vector<string>> requirements;
		map<string, vector<string>> allowedMoves;
		vector<string> moves;
		int steps;

		void initialize() {
			string from, to;
			set<string> unique;
			for (auto &token : this->tokens) {
				tie(from, to) = token;
				requirements[to].push_back(from);
				allowedMoves[from].push_back(to);
				unique.insert(to);
				unique.insert(from);
			}
			this->steps = unique.size();
		}

		vector<string> initialMoves() {
			vector<string> result;
			for (auto &move : allowedMoves) {
				if (requirements.count(move.first) == 0) {
					result.push_back(move.first);
				}
			}
			return result;
		}

		bool isAllowed(string move) {
			for (auto &requirement : this->requirements[move]) {
				if (count(begin(this->moves), end(this->moves), requirement) == 0) {
					return false;
				}
			}
			return true;
		}

		bool isAvailable(string move) {
			return count(begin(this->moves), end(this->moves), move) == 0;
		}

	public:
		Sleigh(vector<tuple<string, string>> tokens) {
			this->tokens = tokens;
			initialize();
		}

		vector<string> move() {
			// is this the first move?
			if (this->moves.size() == 0) {
				return initialMoves();
			}
			// handle other moves
			vector<string> choices;
			for (auto &from : this->moves) {
				for (auto &next : this->allowedMoves[from]) {
					if (isAllowed(next) && isAvailable(next)) {
						choices.push_back(next);
					}
				}
			}
			// since initial moves doesn't show up based on requirements
			// re-add them here
			auto moves = initialMoves();
			for (auto &move : moves) {
				if (isAvailable(move)) {
					choices.push_back(move);
				}
			}

			// sort and remove duplicates
			sort(begin(choices), end(choices));
			auto it = unique(begin(choices), end(choices));
			choices.resize(distance(begin(choices), it));

			return choices;
		}

		void accept(string move) {
			this->moves.push_back(move);
		}

		string path() {
			string result = "";
			for (auto &move : moves) {
				result += move;
			}
			return result;
		}

		bool moreMoves() {
			return this->moves.size() < this->steps;
		}
	};

	string Part1(vector<tuple<string, string>> tokens);

	int Part2(vector<tuple<string, string>> tokens, int elves);
}
