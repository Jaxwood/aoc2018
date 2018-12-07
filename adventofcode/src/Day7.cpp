#include "Day7.h"

using namespace std;

namespace Day7 {

	string getRootNode(vector<tuple<string, string>> tokens) {
		set<string> from;
		set<string> to;
		string stepFrom;
		string stepTo;

		for (int i = 0; i < tokens.size(); i++) {
			tie (stepFrom, stepTo) = tokens[i];
			from.insert(stepFrom);
			to.insert(stepTo);
		}
		set<string> difference;
		set_difference(begin(from), end(from), begin(to), end(to), inserter(difference, end(difference)));

		string result;
		for (auto &it : difference) {
			result = it;
		}
		return result;
	}

	string Part1(vector<tuple<string, string>> tokens) {
		auto root = getRootNode(tokens);
		return "";
	}
}
