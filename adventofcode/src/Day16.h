#pragma once

#include <map>
#include <vector>
#include <string>

namespace Day16 {
	class Instruction {
		std::vector<int> before;
		std::vector<int> after;
		std::vector<int> operation;
		std::vector<int> registry;
		const int OPCODE = 0;
		const int A = 1;
		const int B = 2;
		const int C = 3;
	public:
		Instruction(std::vector<int> before, std::vector<int> after, std::vector<int> operation) {
			this->after = after;
			this->before = before;
			this->operation = operation;
			this->registry = std::vector<int>{ 0, 0, 0, 0 };
		}

		int read(const int registry);
		int readRegistry(int registry);
		int operationCode();
		void setOperation(std::vector<int> operation);
		void run();

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
	int Part2(std::vector<std::vector<int>> operations);
}

