#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Day19 {

	class Instruction {
		std::string operation;
		std::vector<int> operations;
	public:
		Instruction(std::string operation, std::vector<int> operations) : operation(operation), operations(operations) {};
		int read(const int registry);
		std::string type() const;
	};

	class InstructionPointer {
		int ip;
		int A = 0;
		int B = 1;
		int C = 2;
		std::vector<long long> memory;
		void addr(Instruction instruction);
		void addi(Instruction instruction);
		void mulr(Instruction instruction);
		void muli(Instruction instruction);
		void banr(Instruction instruction);
		void bani(Instruction instruction);
		void borr(Instruction instruction);
		void bori(Instruction instruction);
		void setr(Instruction instruction);
		void seti(Instruction instruction);
		void gtir(Instruction instruction);
		void gtri(Instruction instruction);
		void gtrr(Instruction instruction);
		void eqir(Instruction instruction);
		void eqri(Instruction instruction);
		void eqrr(Instruction instruction);
	public:
		InstructionPointer(int ip) {
			this->ip = ip;
			this->memory = std::vector<long long>{ 0, 0, 0, 0, 0, 0 };
		};
		int registry(int num);
		int getInstruction();
		void setRegistery(int registryNum, int registryValue);
		void execute(Instruction instruction);
		std::string log();
	};

	int Part1(InstructionPointer pointer, std::vector<Instruction> instructions);
	int Part2();
}
