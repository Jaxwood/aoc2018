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

	void Dungeon::calculateMove(char c) {
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

	void Dungeon::move(string directions) {
		for (auto &c : directions) {
			this->calculateMove(c);
		}
	}

	set<Room> Dungeon::getRooms(Room room) {
		return this->rooms[room];
	}

	Room Dungeon::getCurrentRoom() {
		return this->current;
	}

	void Dungeon::restore(Room room) {
		this->current = room;
	}

	int Dungeon::size() {
		return this->rooms.size();
	}

	map<Room, int> maxDistance(Dungeon &dungeon)
	{
		vector<Room> path = { make_tuple(0,0) };
		vector<Room> visited;
		map<Room, int> distances = { make_pair(make_tuple(0, 0), 0) };
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

		return distances;
	}

	tuple<string, string> getSegment(string directions) {
		auto len = directions.find('(');
		if (len != string::npos) {
			return make_tuple(directions.substr(0, len), directions.substr(len));
		}
		return make_tuple(directions, "");
	}

	tuple<string, string> getGroup(string directions) {
		int cnt = 0;
		int len = 0;
		for (auto i = 0; i < directions.size(); i++) {
			if (directions[i] == '(') {
				cnt++;
			}
			if (directions[i] == ')') {
				cnt--;
			}
			if (cnt == 0) {
				len = i;
				break;
			}
		}
		return make_tuple(directions.substr(1, len - 1), directions.substr(len+1));
	}

	vector<string> getSplit(string directions) {
		vector<string> result;
		string segment = "";
		int cnt = 0;

		for (auto i = 0; i < directions.size(); i++) {
			auto next = directions[i];
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

	void populateDungeon(Dungeon& dungeon, string directions) {
		char GROUP = '(';
		if (directions[0] != '^' && directions[directions.size()-1] != '$') {
			throw exception("invalid input - should start with ^ and end with $");
		}
		string head, tail;
		Room current = dungeon.getCurrentRoom();
		queue<tuple<string, Room>> segments;
		segments.push(make_tuple(directions.substr(1, directions.size()-2), current));
		while (!segments.empty()) {
			tie (tail, current) = segments.front();
			dungeon.restore(current);
			segments.pop();
			// is it a group?
			if (tail[0] == GROUP) {
				tie (head, tail) = getGroup(tail);
				auto splits = getSplit(head);
				for (auto &split : splits) {
					dungeon.restore(current);
					if (any_of(begin(split), end(split), [GROUP](char c) { return c == GROUP; })) {
						string hd, tl;
						tie (hd, tl) = getSegment(split);
						dungeon.move(hd);
						segments.push(make_tuple(tl, dungeon.getCurrentRoom()));
					}
					else {
						dungeon.move(split);
					}
				}
				if (tail != "") {
					segments.push(make_tuple(tail, dungeon.getCurrentRoom()));
				}
			}
			else { // take until next group
				tie(head, tail) = getSegment(tail);
				dungeon.move(head);
				if (tail != "") {
					segments.push(make_tuple(tail, dungeon.getCurrentRoom()));
				}
			}
		}
	}

	int Part1(string directions) {
		Dungeon dungeon = Dungeon();
		populateDungeon(dungeon, directions);
		auto distances = maxDistance(dungeon);
		auto max = *(max_element(begin(distances), end(distances), [](pair<Room, int> p1, pair<Room, int> p2) {
			return p1.second < p2.second;
		}));
		return max.second;
	}

	int Part2(string directions) {
		Dungeon dungeon = Dungeon();
		populateDungeon(dungeon, directions);
		auto distances = maxDistance(dungeon);
		auto max = count_if(begin(distances), end(distances), [](pair<Room, int> pair) {
			return pair.second >= 1000;
		});
		return max;
	}
}
