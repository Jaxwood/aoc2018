#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

namespace Day8 {

	class Node {
	private:
		vector<Node> children;
		vector<int> metadata;
	public:
		Node(vector<int> metadata) {
			this->metadata = metadata;
		}
		void addChild(Node node) {
			this->children.push_back(node);
		}
		vector<Node> nodes() {
			return this->children;
		}
		vector<int> meta() {
			return this->metadata;
		}
		bool hasNodes() {
			return this->children.size() > 0;
		}
		bool hasChild(int idx) {
			return this->children.size() > idx;
		}
	};

	int Part1(vector<int> licenseFile);

	int Part2(vector<int> licenseFile);
}
