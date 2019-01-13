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

	vector<string> split(int idx, int size, string raw) {
		vector<string> result;
		string segment = "";
		int cnt = 0;
		// trim ends
		raw = raw.substr(idx + 1, size - 2);

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

	vector<string> expand(int idx, string directions) {
		int size = group(idx, directions);
		auto sections = split(idx, size, directions);
		vector<string> result;
		for (auto &section : sections) {
			if (count(begin(section), end(section), '(') == 0) {
				result.push_back(section);
			}
			else {
				auto location = section.find('(');
				int size = group(location, section);
				auto tail = section.substr(location + size);
				auto head = section.substr(0, location);
				for (auto ex : expand(location, section)) {
					result.push_back(head + ex + tail);
				}
			}
		}
		return result;
	}

	int Dungeon::size() {
		return this->rooms.size();
	}

	int Part1(string directions) {
		Dungeon dungeon = Dungeon();
		int idx = 1;
		char c = directions[idx];
		while(c != '$') {
			if (c == '(') {
				dungeon.checkpoint();
				int size = group(idx, directions);
				auto sections = expand(idx, directions);
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
