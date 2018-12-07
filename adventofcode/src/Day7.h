#pragma once

#include <string>
#include <vector>
#include <tuple>

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

		string getName() {
			return this->name;
		}
	};
	string Part1(vector<tuple<string, string>> tokens);
}
