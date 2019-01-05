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
		std::vector<int> registers;
	public:
		Instruction(std::string operation, std::vector<int> registers) : operation(operation), registers(registers) {};
	};
	int Part1(InstructionPointer pointer, std::vector<Instruction> instructions);
}
