#include "Day20.h"

using namespace std;

namespace Day20 {

	char NORTH = 'N';
	char SOUTH = 'S';
	char EAST = 'E';
	char WEST = 'W';
	char BEGIN = '^';
	char END = '$';
	char OPEN = '(';
	char CLOSE = ')';
	char PIPE = '|';

	Point move(Point current, char c) {
		int x, y;
		tie(x, y) = current;
		if (c == NORTH) {
			return make_tuple(x, y + 1);
		}
		else if (c == SOUTH) {
			return make_tuple(x, y - 1);
		}
		else if (c == WEST) {
			return make_tuple(x - 1, y);
		}
		else if (c == EAST) {
			return make_tuple(x + 1, y);
		}
		throw exception("unknown char: " + c);
	}

	class Vertex {
		vector<Vertex> edges;
		Point vertice;
		char direction;
	public:
		Vertex(char c, Point point) {
			this->vertice = point;
			this->direction = c;
		}
		void append(Vertex vertex) {
			this->edges.push_back(vertex);
		}
		Point location() {
			return this->vertice;
		}
	};

	string group(string raw) {
		int cnt = 0;
		int size = 0;
		do {
			if (raw[size] == CLOSE) {
				cnt--;
			}
			if (raw[size] == OPEN) {
				cnt++;
			}
			size++;
		} while (cnt != 0);
		return raw.substr(0,size);
	}

	vector<string> split(string raw) {
		vector<string> result;
		string segment = "";
		int cnt = 0;
		// trim ends
		raw = raw.substr(1, raw.size() - 2);

		for (auto i = 0; i < raw.size(); i++) {
			auto next = raw[i];
			if (next == OPEN) {
				cnt++;
			}
			if (next == CLOSE) {
				cnt--;
			}
			if (next == PIPE && cnt == 0) {
				result.push_back(segment);
				segment = "";
			}
			else {
				segment += next;
			}
		}
		result.push_back(segment);

		return result;
	}

	Vertex build(Vertex node, string raw) {
		if (raw.size() == 0) {
			return node;
		}
		char c = raw[0];
		if (c == END) {
			return node;
		}
		if (c == OPEN) {
		}
		else if (c == CLOSE) {
			throw exception("encounter close character");
		}
		else {
			auto next = Vertex(c, move(node.location(), c));
			node.append(build(next, raw.substr(1)));
			return node;
		}
	}

	int Part1(string raw) {
		auto root = build(Vertex('^', make_tuple(0, 0)), raw.substr(1));
		return 0;
	}
}
