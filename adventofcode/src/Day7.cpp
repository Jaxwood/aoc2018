#include "Day7.h"

using namespace std;

namespace Day7 {

	Node getRootNode(vector<tuple<string, string>> tokens) {
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
		return Node(result);
	}

	Node populate(Node n, vector<tuple<string, string>> tokens) {
		auto parent = n.getName();
		string from, to;
		for (int i = 0; i < tokens.size(); i++) {
			tie (from, to) = tokens[i];
			if (from == parent) {
				auto child = Node(to);
				child = populate(child, tokens);
				n.addChild(child);
			}
		}
		return n;
	}

	string sum(Node n) {
		string result = n.getName();
		for (auto c : n.children())
		{
			result += c.getName();
		}
		return result;
	}

	string Part1(vector<tuple<string, string>> tokens) {
		auto root = getRootNode(tokens);
		auto tree = populate(root, tokens);
		return sum(tree);
	}
}
