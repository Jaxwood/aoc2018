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
		std::string reciepes;
	public:
		Reciepe(std::string initial);
		std::vector<Elv> produce(std::vector<Elv> elves);
		int size();
		std::string result(int count);
	};

	std::string Part1(int recipes);
}
