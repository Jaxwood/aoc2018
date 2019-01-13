#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

namespace Day20 {
	typedef std::tuple<int, int> Room;

	class Dungeon {
		char NORTH = 'N';
		char SOUTH = 'S';
		char EAST = 'E';
		char WEST = 'W';
		char BEGIN = '^';
		char END = '$';
		char OPEN = '(';
		char CLOSE = ')';
		char PIPE = '|';

		std::map<Room, std::set<Room>> rooms;
		Room current;
		Room store;
	public:
		Dungeon();
		void addRoom(Room number);
		void move(char direction);
		void restore();
		void checkpoint();
		int size();
		std::set<Room> getRooms(Room room);
	};

	int Part1(std::string input);
}
