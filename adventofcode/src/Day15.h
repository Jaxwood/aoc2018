#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

namespace Day15 {

	typedef std::tuple<int, int> Point;

	class Atlas {
		const int size = 10;
		const char OPEN = '.';
		char grid[10][10];
	public:
		void initialize(std::vector<std::string> raw);
		bool equal(const Atlas &other) const;
		void swap(const Point p1, const Point p2);
		void clear(const Point point);
		char at(const Point point) const;
		std::vector<Point> neighbors(const Point point) const;
		std::vector<Point> types(const char c) const;
		bool adjacent(Point p1, Point p2);
	};

	bool operator==(const Atlas &a1, const Atlas &a2);

	class Player {
		Point location;
		int hitpoints;
		bool elf;
	public:
		Player(Point location, bool isElf, int hitpoints);
		bool alive() const;
		void attack(Player* player) const;
		Point position() const;
		bool canReach(Player *opponent) const;
		void takehit();
		bool operator<(Player &other) const;
		void move(const Point destination);
		bool isElf() const;
		int health() const;
	};

	bool operator==(const Player &p1, const Player &p2);

	class PathFinder {
		Atlas *atlas;
	public:
		PathFinder(Atlas *atlas);
		std::vector<Point> targetLocations(std::vector<Point> &targets);
		Point move(Point from);
		std::vector<Point> targets(Point from);
		std::map<Point, int> reachable(Point from, std::vector<Point> &targets);
		int nearest(Point from, Point target, std::map<Point, Point> parents);
		std::vector<Point> shortestPath(std::map<Point, int> paths);
		Point selectByReadingOrder(std::vector<Point> paths);
		Point selectMove(Point from, Point to);
		bool isAtTarget(Point from, std::vector<Point> &targets);
	};

	class Game {
		std::vector<Player> players;
		int turns;
	public:
		Game(std::vector<Player> players);
		bool over();
		Player* attack(Player player);
		void order();
		Player move(Player player, Point to);
		std::vector<Player> participants();
		void turn();
		int score();
		void sync();
	};

	bool sortPoints(Point p1, Point p2);

	int Part1(std::vector<std::string> lines);
}
