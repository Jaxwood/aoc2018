#pragma once

#include <vector>

namespace Day19 {
	class InstructionPointer {
		int registry;
	public:
		InstructionPointer(int registry) : registry(registry) {};
	};
	class Instruction {
		std::string operation;
		std::vector<int> operations;
	public:
		Instruction(std::string operation, std::vector<int> operations) : operation(operation), operations(operations) {};
		int read(const int registry);
		std::string type() const;
	};
	class Device {
		int A = 0;
		int B = 0;
		int C = 0;
		std::vector<int> memory;
	public:
		Device();
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
	};
	int Part1(InstructionPointer pointer, std::vector<Instruction> instructions);
}
