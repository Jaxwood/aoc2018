#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

namespace Day7 {

	class Node {
	private:
		vector<Node> nodes;
		string name;
	public:
		Node(string name) {
			this->name = name;
		}

		void addChild(Node node) {
			nodes.push_back(node);
		}

		vector<Node> children() {
			return this->nodes;
		}

		string getName() {
			return this->name;
		}
	};
	string Part1(vector<tuple<string, string>> tokens);
}
