#include "Day8.h"

namespace Day8 {
	vector<int> getMetadata(int metadataCount, vector<int>& data) {
		vector<int> metadata;
		for (int i = 0; i < metadataCount; i++) {
			int value = data.back();
			data.pop_back();
			metadata.push_back(value);
		}
		return metadata;
	}

	Node build(Node node, vector<int>& data, int childCount) {
		vector<int> metadata;
		if (data.size() == 0) {
			return node;
		}
		// no child nodes?
		if (childCount == 0) {
			int count = data.back();
			data.pop_back();
			metadata = getMetadata(count, data);
			return Node(metadata);
		}
		else {
			int metadataCount = data.back();
			vector<Node> children;
			data.pop_back();
			for (int i = 0; i < childCount; i++) {
				int count = data.back();
				data.pop_back();
				node = build(node, data, count);
				children.push_back(node);
			}
			metadata = getMetadata(metadataCount, data);
			auto parent = Node(metadata);
			for (auto &child : children) {
				parent.addChild(child);
			}
			return parent;
		}
	}

	int sumMetadata(int sum, Node tree) {
		for (auto &node : tree.nodes()) {
			sum = sumMetadata(sum, node);
		}
		auto metadata = tree.meta();
		sum += accumulate(begin(metadata), end(metadata), 0);

		return sum;
	}

	int Part1(vector<int> licenseFile) {
		vector<int> metadata;
		vector<Node> children;
		// get the first child count
		int childCount = licenseFile.back();
		licenseFile.pop_back();
		auto tree = build(Node(metadata), licenseFile, childCount);

		return sumMetadata(0, tree);
	}
}
