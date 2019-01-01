#include "Day16.h"

using namespace std;

namespace Day16 {

	int Instruction::read(const int registry) {
		return this->operation[registry];
	}

	bool Instruction::addr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] + this->before[this->read(this->B)];
		return this->after == registry;
	}
	bool Instruction::addi() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] + this->read(this->B);
		return this->after == registry;
	}
	bool Instruction::mulr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] * this->before[this->read(this->B)];
		return this->after == registry;
	}
	bool Instruction::muli() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] * this->read(this->B);
		return this->after == registry;
	}
	bool Instruction::banr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] & this->before[this->read(this->B)];
		return this->after == registry;
	}
	bool Instruction::bani() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] & this->read(this->B);
		return this->after == registry;
	}
	bool Instruction::borr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] | this->before[this->read(this->B)];
		return this->after == registry;
	}
	bool Instruction::bori() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] | this->read(this->B);
		return this->after == registry;
	}
	bool Instruction::setr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)];
		return this->after == registry;
	}
	bool Instruction::seti() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->read(this->A);
		return this->after == registry;
	}
	bool Instruction::gtir() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->read(this->A) > this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}
	bool Instruction::gtri() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] > this->read(this->B) ? 1 : 0;
		return this->after == registry;
	}
	bool Instruction::gtrr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] > this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}
	bool Instruction::eqir() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->read(this->A) == this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}
	bool Instruction::eqri() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] == this->read(this->B) ? 1 : 0;
		return this->after == registry;
	}
	bool Instruction::eqrr() {
		auto registry = this->before;
		registry[this->read(this->C)] = this->before[this->read(this->A)] == this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}

	int Part1(vector<Instruction> instructions) {
		int total = 0;
		for (auto &instruction : instructions) {
			int run = 0;
			if (instruction.addr()) {
				run++;
			}
			if (instruction.addi()) {
				run++;
			}
			if (instruction.mulr()) {
				run++;
			}
			if (instruction.muli()) {
				run++;
			}
			if (instruction.banr()) {
				run++;
			}
			if (instruction.bani()) {
				run++;
			}
			if (instruction.borr()) {
				run++;
			}
			if (instruction.bori()) {
				run++;
			}
			if (instruction.setr()) {
				run++;
			}
			if (instruction.seti()) {
				run++;
			}
			if (instruction.gtir()) {
				run++;
			}
			if (instruction.gtri()) {
				run++;
			}
			if (instruction.gtrr()) {
				run++;
			}
			if (instruction.eqir()) {
				run++;
			}
			if (instruction.eqri()) {
				run++;
			}
			if (instruction.eqrr()) {
				run++;
			}
			if (run >= 3) {
				total++;
			}
		}
		return total;
	}
}
