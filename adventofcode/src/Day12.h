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
		int zeroIndex = 0;

		// adds 3 dots to the start if missing
		void prefix() {
			int dist = 3 - distance(begin(this->state), find(begin(this->state), end(this->state), '#'));
			this->state = string(dist, '.') + this->state;
			this->zeroIndex += dist;
		}

		// adds 3 dots to the end if missing
		void postfix() {
			auto it = find_end(begin(this->state), end(this->state), begin(this->pattern), end(this->pattern));
			auto dist = 3 - (this->state.size() - distance(begin(this->state), it) - 1);
			this->state = this->state + string(dist, '.');
		}

	public:
		Garden(string state, unordered_map<string, string> rules) {
			this->state = state;
			this->rules = rules;
			this->prefix();
			this->postfix();
		}

		void grow() {
			vector<string> generation;
			int cnt = 0;
			for (int i = 2; i < this->state.size() - 2; i++) {
				string pattern = this->state.substr(i - 2, 5);
				auto it = this->rules.find(pattern);
				if (it != this->rules.end()) {
					auto value = (*it).second;
					generation.push_back(value);
				}
				else {
					generation.push_back(".");
				}
				if (i == 2) {
					this->zeroIndex = this->zeroIndex - 2;
				}
			}
			this->state = "";
			for (int i = 0; i < generation.size(); i++) {
				this->state += generation[i];
			}

			this->prefix();
			this->postfix();
		}

		string layout() {
			return this->state;
		}

		int plants() {
			int sum = 0;
			string positives, negatives;
			copy(begin(this->state) + this->zeroIndex, end(this->state), back_inserter(positives));
			copy(begin(this->state), begin(this->state) + this->zeroIndex + 1, back_inserter(negatives));

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
