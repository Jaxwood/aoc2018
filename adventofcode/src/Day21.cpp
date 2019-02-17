#include "Day21.h"

using namespace Day19;

namespace Day21 {
	int Part1(InstructionPointer pointer, std::vector<Instruction> instructions) {
		int operationCount = 0;
		while (true) {
			auto instructionNum = pointer.getInstruction();
			if (instructionNum < 0 || instructionNum >= instructions.size()) {
				break;
			}
			auto instruction = instructions[instructionNum];
			pointer.execute(instruction);
			operationCount++;
		}
		return operationCount;
	}
}
