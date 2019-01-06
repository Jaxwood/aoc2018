#include "Day19.h"

using namespace std;

namespace Day19 {

	int InstructionPointer::registry(int num) {
		if (num == this->ip) {
			return this->memory[num] - 1;
		}
		else {
			return this->memory[num];
		}
	}

	int InstructionPointer::getInstruction() {
		return this->memory[this->ip];
	}

	void InstructionPointer::execute(Instruction instruction) {
		auto t = instruction.type();
		if (t == "addr") {
			this->addr(instruction);
		}
		if (t == "addi") {
			this->addi(instruction);
		}
		if (t == "mulr") {
			this->mulr(instruction);
		}
		if (t == "muli") {
			this->muli(instruction);
		}
		if (t == "banr") {
			this->banr(instruction);
		}
		if (t == "bani") {
			this->bani(instruction);
		}
		if (t == "borr") {
			this->borr(instruction);
		}
		if (t == "bori") {
			this->bori(instruction);
		}
		if (t == "setr") {
			this->setr(instruction);
		}
		if (t == "seti") {
			this->seti(instruction);
		}
		if (t == "gtir") {
			this->gtir(instruction);
		}
		if (t == "gtri") {
			this->gtri(instruction);
		}
		if (t == "gtrr") {
			this->gtrr(instruction);
		}
		if (t == "eqir") {
			this->eqir(instruction);
		}
		if (t == "eqri") {
			this->eqri(instruction);
		}
		if (t == "eqrr") {
			this->eqrr(instruction);
		}
		this->memory[this->ip]++;
	}

	void InstructionPointer::addr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] + this->memory[instruction.read(this->B)];
	}

	void InstructionPointer::addi(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] + instruction.read(this->B);
	}

	void InstructionPointer::mulr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] * this->memory[instruction.read(this->B)];
	}

	void InstructionPointer::muli(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] * instruction.read(this->B);
	}

	void InstructionPointer::banr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] & this->memory[instruction.read(this->B)];
	}

	void InstructionPointer::bani(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] & instruction.read(this->B);
	}

	void InstructionPointer::borr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] | this->memory[instruction.read(this->B)];
	}

	void InstructionPointer::bori(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] | instruction.read(this->B);
	}

	void InstructionPointer::setr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)];
	}

	void InstructionPointer::seti(Instruction instruction) {
		this->memory[instruction.read(this->C)] = instruction.read(this->A);
	}

	void InstructionPointer::gtir(Instruction instruction) {
		this->memory[instruction.read(this->C)] = instruction.read(this->A) > this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	void InstructionPointer::gtri(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] > instruction.read(this->B) ? 1 : 0;
	}

	void InstructionPointer::gtrr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] > this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	void InstructionPointer::eqir(Instruction instruction) {
		this->memory[instruction.read(this->C)] = instruction.read(this->A) == this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	void InstructionPointer::eqri(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] == instruction.read(this->B) ? 1 : 0;
	}

	void InstructionPointer::eqrr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] == this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	string InstructionPointer::log() {
		string result;
		for (size_t i = 0; i < this->memory.size(); i++) {
			result += "\t" + to_string(this->memory[i]);
		}
		return result;
	}

	int Instruction::read(const int registry) {
		return this->operations[registry];
	}

	string Instruction::type() const {
		return this->operation;
	}

	void dump(vector<string> logs) {
		std::ofstream out("output.txt");
		for (auto str : logs) {
			out << str << endl;
		}
	}

	int Part1(InstructionPointer pointer, vector<Instruction> instructions) {
		while (true) {
			auto instructionNum = pointer.getInstruction();
			if (instructionNum < 0 || instructionNum >= instructions.size()) {
				break;
			}
			auto instruction = instructions[instructionNum];
			pointer.execute(instruction);
		}
		return pointer.registry(0);
	}

	int Part2() {
		// register 0 is being increment every time register 2 is dividable with the current value in register 1.
		// register 1 is being incremented with 1 every 10551282 tick.
		// runs from 1 to the value of register 2 which is 10551282 in this case.
		long long sum = 0;
		int reg1 = 1;
		for (auto reg1 = 1; reg1 <= 10551282; reg1++) {
			if (10551282 % reg1 == 0) {
				sum = sum + reg1;
			}
		}
		return sum;
	}
}
