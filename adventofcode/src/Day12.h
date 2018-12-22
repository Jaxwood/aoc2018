#pragma once

#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>

using namespace std;

namespace Day12 {
	class Garden {
	private:
		string state;
		vector<char> pattern = { '#' };
		unordered_map<string, string> rules;
		unordered_map<string, vector<string>> cache;
		int idx;

		// adds 3 dots to the start if missing
		void prefix() {
			int dist = 5 - distance(begin(this->state), find(begin(this->state), end(this->state), '#'));
			this->state = string(dist, '.') + this->state;
		}

		// adds 3 dots to the end if missing
		void postfix() {
			auto it = find_end(begin(this->state), end(this->state), begin(this->pattern), end(this->pattern));
			auto dist = 5 - (this->state.size() - distance(begin(this->state), it) - 1);
			this->state = this->state + string(dist, '.');
		}

	public:
		Garden(string state, unordered_map<string, string> rules) {
			this->state = state;
			this->rules = rules;
			this->idx = 0;
		}

		void grow() {
			this->prefix();
			this->postfix();
			this->idx -= 3;

			vector<string> generation;
			bool found = false;
			for (int i = 2; i < this->state.size() - 2; i++) {
				string pattern = this->state.substr(i - 2, 5);
				string value = ".";
				auto it = this->rules.find(pattern);
				if (it != this->rules.end()) {
					value = (*it).second;
				}
				generation.push_back(value);
				if (!found && value == "#") {
					this->idx += (i - 2);
					found = true;
				}
			}
			this->state = "";
			for (int i = 0; i < generation.size(); i++) {
				this->state += generation[i];
			}

		}

		string layout() {
			return this->state;
		}

		int plants() {
			int sum = 0;
			string positives, negatives;
			int dist = abs(this->idx) + distance(begin(this->state), find(begin(this->state), end(this->state), '#'));
			copy(begin(this->state) + dist, end(this->state), back_inserter(positives));
			copy(begin(this->state), begin(this->state) + dist + 1, back_inserter(negatives));

			for (int i = 0; i < positives.size(); i++) {
				if (positives[i] == '#') {
					sum += i;
				}
			}
			reverse(begin(negatives), end(negatives));
			for (int i = 0; i <= negatives.size(); i++) {
				if (negatives[i] == '#') {
					sum -= i;
				}
			}
			return sum;
		}
	};

	int Part1(string initialState, unordered_map<string, string> input);
}
