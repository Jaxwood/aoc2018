#include "Day20.h"

using namespace std;

namespace Day20 {
	Dungeon::Dungeon() {
		this->current = make_tuple(0, 0);
	}

	void Dungeon::addRoom(Room number) {
		this->rooms[this->current].insert(number);
		this->rooms[number].insert(this->current);
	}

	void Dungeon::move(char c) {
		int x, y;
		tie(x, y) = this->current;
		Room next;
		if (c == this->BEGIN) {
			return;
		}
		if (c == this->END) {
			return;
		}
		if (c == this->NORTH) {
			next = make_tuple(x, y + 1);
		}
		else if (c == this->SOUTH) {
			next = make_tuple(x, y - 1);
		}
		else if (c == this->WEST) {
			next = make_tuple(x - 1, y);
		}
		else if (c == this->EAST) {
			next = make_tuple(x + 1, y);
		}
		else {
			throw exception("unknown character");
		}
		this->addRoom(next);
		this->current = next;
	}

	set<Room> Dungeon::getRooms(Room room) {
		return this->rooms[room];
	}

	void Dungeon::checkpoint() {
		this->store = this->current;
	}

	void Dungeon::restore() {
		this->current = this->store;
	}

	int group(int idx, string raw) {
		int cnt = 0;
		int size = idx;
		do {
			if (raw[size] == ')') {
				cnt--;
			}
			if (raw[size] == '(') {
				cnt++;
			}
			size++;
		} while (cnt != 0);
		return size - idx;
	}

	vector<string> split(string raw) {
		vector<string> result;
		string segment = "";
		int cnt = 0;
		// trim ends
		raw = raw.substr(1, raw.size() - 2);

		for (auto i = 0; i < raw.size(); i++) {
			auto next = raw[i];
			if (next == '(') {
				cnt++;
			}
			if (next == ')') {
				cnt--;
			}
			if (next == '|' && cnt == 0) {
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

	vector<string> expand(string directions) {
		vector<string> result;
		auto sections = split(directions);
		while (!sections.empty()) {
			auto candidate = sections.back();
			sections.pop_back();
			if(count(begin(candidate), end(candidate), '(') > 0) {
				int idx = candidate.find('(');
				auto prefix = idx != string::npos ? candidate.substr(0, idx) : "";
				int size = group(idx, candidate);
				auto postfix = candidate.size() != (size + idx) ? candidate.substr(idx + size) : "";
				auto candidates = expand(candidate.substr(idx, size));
				for (auto &next : candidates) {
					result.push_back(prefix + next + postfix);
				}
			}
			else {
				result.push_back(candidate);
			}
		}
		return result;
	}

	int Dungeon::size() {
		return this->rooms.size();
	}

	int Part1(string directions) {
		Dungeon dungeon = Dungeon();
		int idx = 0;
		if (directions[idx] != '^') {
			throw exception("unexpected character");
		}
		char c = directions[++idx];
		while(c != '$') {
			if (c == '(') {
				dungeon.checkpoint();
				int size = group(idx, directions);
				auto sections = expand(directions.substr(idx, size));
				for (auto &section : sections) {
					for (auto n : section) {
						dungeon.move(n);
					}
					dungeon.restore();
				}
				idx += size;
			}
			else {
				dungeon.move(c);
				idx++;
			}
			c = directions[idx];
		}

		vector<Room> path = { make_tuple(0,0) };
		vector<Room> visited;
		map<Room, int> distances;
		distances[make_tuple(0, 0)] = 0;
		while (!path.empty()) {
			auto room = path.back();
			path.pop_back();
			if (count(begin(visited), end(visited), room) == 0) {
				visited.push_back(room);
				for (auto &r : dungeon.getRooms(room)) {
					if (count(begin(visited), end(visited), r) == 0) {
						path.push_back(r);
						distances[r] = distances[room] + 1;
					}
				}
			}
		}

		auto max = *(max_element(begin(distances), end(distances), [](pair<Room, int> p1, pair<Room, int> p2) {
			return p1.second < p2.second;
		}));
		return max.second;
	}
}
