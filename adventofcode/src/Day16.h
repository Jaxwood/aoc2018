#pragma once

#include <vector>
#include <string>

namespace Day16 {
	class Instruction {
		std::vector<int> before;
		std::vector<int> after;
		std::vector<int> operation;
	public:
		Instruction(std::vector<int> before, std::vector<int> after, std::vector<int> operation) {
			this->after = after;
			this->before = before;
			this->operation = operation;
		}
	};
	int Part1(std::vector<Instruction> lines);
}

