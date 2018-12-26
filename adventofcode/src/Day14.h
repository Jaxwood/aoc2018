#pragma once

#include <string>
#include <vector>

namespace Day14 {
	class Elv {
	private:
		int idx;
		int offset;
	public:
		Elv(int index, int offset);
		void setNextIndex(int index);
		void updateOffset(int size);
		int getIndex();
		int getOffset();
	};

	class Reciepe {
	private:
		std::vector<int> reciepes;
		std::string target;
		int cnt;
	public:
		Reciepe(std::string initial, std::string target);
		void produce(std::vector<Elv> &elves);
		int size();
		int count();
		std::string result(int count, int length);
		bool match(std::string target);
	};

	std::string Part1(int recipes);

	int Part2(std::string recipes);
}
