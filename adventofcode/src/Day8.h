#pragma once

#include <vector>

using namespace std;

namespace Day8 {

	class Node {
	private:
		vector<Node> children;
		vector<int> metadata;
	public:
		Node(vector<Node> children, vector<int> metadata) {
			this->metadata = metadata;
			this->children = children;
		}
		Node(vector<int> metadata) {
			this->metadata = metadata;
		}
		void addChild(Node node) {
			this->children.push_back(node);
		}
	};

	int Part1(vector<int> licenseFile);
}
