#include "Day19.h"

using namespace std;

namespace Day19 {

	Device::Device() {
		this->memory = vector<int>{ 0, 0, 0, 0, 0, 0 };
	}

	void Device::addr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] + this->memory[instruction.read(this->B)];
	}

	void Device::addi(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] + instruction.read(this->B);
	}

	void Device::mulr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] * this->memory[instruction.read(this->B)];
	}

	void Device::muli(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] * instruction.read(this->B);
	}

	void Device::banr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] & this->memory[instruction.read(this->B)];
	}

	void Device::bani(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] & instruction.read(this->B);
	}

	void Device::borr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] | this->memory[instruction.read(this->B)];
	}

	void Device::bori(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] | instruction.read(this->B);
	}

	void Device::setr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)];
	}

	void Device::seti(Instruction instruction) {
		this->memory[instruction.read(this->C)] = instruction.read(this->A);
	}

	void Device::gtir(Instruction instruction) {
		this->memory[instruction.read(this->C)] = instruction.read(this->A) > this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	void Device::gtri(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] > instruction.read(this->B) ? 1 : 0;
	}

	void Device::gtrr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] > this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	void Device::eqir(Instruction instruction) {
		this->memory[instruction.read(this->C)] = instruction.read(this->A) == this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	void Device::eqri(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] == instruction.read(this->B) ? 1 : 0;
	}

	void Device::eqrr(Instruction instruction) {
		this->memory[instruction.read(this->C)] = this->memory[instruction.read(this->A)] == this->memory[instruction.read(this->B)] ? 1 : 0;
	}

	int Instruction::read(const int registry) {
		return this->operations[registry];
	}

	string Instruction::type() const {
		return this->operation;
	}

	int Part1(InstructionPointer pointer, vector<Instruction> instructions) {
		auto device = Device();
		for (auto &instruction : instructions) {
			auto t = instruction.type();
			if (t == "addr") {
				device.addr(instruction);
			}
			if (t == "addi") {
				device.addi(instruction);
			}
			if (t == "mulr") {
				device.mulr(instruction);
			}
			if (t == "muli") {
				device.muli(instruction);
			}
			if (t == "banr") {
				device.banr(instruction);
			}
			if (t == "bani") {
				device.bani(instruction);
			}
			if (t == "borr") {
				device.borr(instruction);
			}
			if (t == "bori") {
				device.bori(instruction);
			}
			if (t == "setr") {
				device.setr(instruction);
			}
			if (t == "seti") {
				device.seti(instruction);
			}
			if (t == "gtir") {
				device.gtir(instruction);
			}
			if (t == "gtri") {
				device.gtri(instruction);
			}
			if (t == "gtrr") {
				device.gtrr(instruction);
			}
			if (t == "eqir") {
				device.eqir(instruction);
			}
			if (t == "eqri") {
				device.eqri(instruction);
			}
			if (t == "eqrr") {
				device.eqrr(instruction);
			}
		}
		return 0;
	}

}
