#include "Day21.h"

using namespace Day19;
using namespace std;

#include <set>

namespace Day21 {

	int Part1(InstructionPointer pointer, std::vector<Instruction> instructions) {
		pointer.setRegistery(0, 0);
		while (true) {
			auto instructionNum = pointer.getInstruction();
			if (instructionNum < 0 || instructionNum >= instructions.size()) {
				break;
			}
			auto instruction = instructions[instructionNum];
			pointer.execute(instruction);

			// instruction number 28 is the equality comparision between reg1 and reg3
			// that causes the program to halt if they are equal
			if (instructionNum == 28) {
				return pointer.registry(3);
			}
		}
	}

	int Part2() {
		// initilize registeries
		long long reg1 = 0;
		long long reg2 = 0;
		long long reg3 = 2176960;
		long long reg4 = 65536;
		long long reg5 = 0;
		set<long long> candidates;

		// the algorithm boils down to the following instructions
		while (true) {
			reg1 = reg4 & 255;
			reg3 = reg3 + reg1;
			reg3 = reg3 & 16777215;
			reg3 = reg3 * 65899;
			reg3 = reg3 & 16777215;

			// this is the condition for finding a match
			if (256 > reg4) {
				// max unqiue matches is 10295 - get the last unqiue match as the result
				if (candidates.size() == 10295 - 1) {
					return reg3;
				}
				candidates.insert(reg3);
				reg2 = reg1 + reg2;
				reg4 = reg3 | 65536;
				reg3 = 2176960;
			}
			else
			{
				reg5 = reg4 / 256 + 1;
				reg1 = reg5 - 1;
				reg4 = reg1;
			}
		}
	}
}
