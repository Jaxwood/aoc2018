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

	vector<string> paths(vector<string> acc, string raw) {
		if (raw.size() == 0) return acc;
		char direction = raw[0];
		if (direction == BEGIN) return paths(acc, raw.substr(1));
		if (direction == END) return acc;

		if (direction == OPEN) {
			int size;
			string section;
			tie(size, section) = group(raw);
			auto choices = split(section);
			vector<string> result;
			for (auto &c : choices) {
				for (auto &r : paths(acc, c)) {
					result.push_back(r);
				}
			}
			return paths(result, raw.substr(size));
		}
		if (acc.size() == 0) {
			acc.push_back(string(1, direction));
		}
		else {
			for (size_t i = 0; i < acc.size(); i++) {
				acc[i].append(string(1, direction));
			}
		}
		return paths(acc, raw.substr(1));
	}

	int Part1(string raw) {
		auto root = paths(vector<string>(), raw);
		return 0;
	}
}
