#pragma once

#include <vector>
#include <string>

namespace Day16 {
	class Instruction {
		std::vector<int> before;
		std::vector<int> after;
		std::vector<int> operation;
		const int OPCODE = 0;
		const int A = 1;
		const int B = 2;
		const int C = 3;
	public:
		Instruction(std::vector<int> before, std::vector<int> after, std::vector<int> operation) {
			this->after = after;
			this->before = before;
			this->operation = operation;
		}

		int read(const int registry);

		bool addr();
		bool addi();
		bool mulr();
		bool muli();
		bool banr();
		bool bani();
		bool borr();
		bool bori();
		bool setr();
		bool seti();
		bool gtir();
		bool gtri();
		bool gtrr();
		bool eqir();
		bool eqri();
		bool eqrr();
	};
	int Part1(std::vector<Instruction> lines);
}

