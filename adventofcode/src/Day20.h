#pragma once

#include <algorithm>
#include <map>
#include <queue>
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

		void calculateMove(char direction);
	public:
		Dungeon();
		void addRoom(Room number);
		void move(std::string directions);
		void restore(Room room);
		Room getCurrentRoom();
		int size();
		std::set<Room> getRooms(Room room);
	};

	int Part1(std::string input);
}
