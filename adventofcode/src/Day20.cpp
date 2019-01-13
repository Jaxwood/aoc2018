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

	tuple<int,string> group(string raw) {
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
		return make_tuple(size, raw.substr(0, size));
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

	vector<string> paths(vector<string> acc) {
		vector<string> outer;
		while (true) {
			vector<string> result;
			for (auto &a : acc) {
				string str; int size;
				int idx = a.find(OPEN);
				if (idx == -1) {
					outer.push_back(a);
					continue;
				}
				auto head = a.substr(0, idx);
				tie(size,str) = group(a.substr(idx));
				auto choices = split(str);
				auto tail = a.substr(idx+size);
				for (auto &choice : choices) {
					result.push_back(head + choice + tail);
				}
			}
			acc = result;
			if (all_of(begin(acc), end(acc), [](string str) { return str.find(OPEN) == -1; })){
				copy(begin(acc), end(acc), back_inserter(outer));
				break;
			}
		}
		return outer;
	}

	int Part1(string raw) {
		auto root = paths(vector<string> { raw });
		int cnt = 0;
		for (auto &r : root) {
			if (r.size() > cnt) {
				cnt = r.size();
			}
		}
		return cnt;
	}
}
