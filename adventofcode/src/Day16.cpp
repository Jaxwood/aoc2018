#include "Day16.h"

using namespace std;

namespace Day16 {

	bool Instruction::addr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] + this->registry[this->read(this->B)];
		registry[this->read(this->C)] = this->before[this->read(this->A)] + this->before[this->read(this->B)];
		return this->after == registry;
	}

	bool Instruction::addi() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] + this->read(this->B);
		registry[this->read(this->C)] = this->before[this->read(this->A)] + this->read(this->B);
		return this->after == registry;
	}

	bool Instruction::mulr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] * this->registry[this->read(this->B)];
		registry[this->read(this->C)] = this->before[this->read(this->A)] * this->before[this->read(this->B)];
		return this->after == registry;
	}

	bool Instruction::muli() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] * this->read(this->B);
		registry[this->read(this->C)] = this->before[this->read(this->A)] * this->read(this->B);
		return this->after == registry;
	}

	bool Instruction::banr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] & this->registry[this->read(this->B)];
		registry[this->read(this->C)] = this->before[this->read(this->A)] & this->before[this->read(this->B)];
		return this->after == registry;
	}

	bool Instruction::bani() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] & this->read(this->B);
		registry[this->read(this->C)] = this->before[this->read(this->A)] & this->read(this->B);
		return this->after == registry;
	}

	bool Instruction::borr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] | this->registry[this->read(this->B)];
		registry[this->read(this->C)] = this->before[this->read(this->A)] | this->before[this->read(this->B)];
		return this->after == registry;
	}

	bool Instruction::bori() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] | this->read(this->B);
		registry[this->read(this->C)] = this->before[this->read(this->A)] | this->read(this->B);
		return this->after == registry;
	}

	bool Instruction::setr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)];
		registry[this->read(this->C)] = this->before[this->read(this->A)];
		return this->after == registry;
	}

	bool Instruction::seti() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->read(this->A);
		registry[this->read(this->C)] = this->read(this->A);
		return this->after == registry;
	}

	bool Instruction::gtir() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->read(this->A) > this->registry[this->read(this->B)] ? 1 : 0;
		registry[this->read(this->C)] = this->read(this->A) > this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}

	bool Instruction::gtri() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] > this->read(this->B) ? 1 : 0;
		registry[this->read(this->C)] = this->before[this->read(this->A)] > this->read(this->B) ? 1 : 0;
		return this->after == registry;
	}

	bool Instruction::gtrr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] > this->registry[this->read(this->B)] ? 1 : 0;
		registry[this->read(this->C)] = this->before[this->read(this->A)] > this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}

	bool Instruction::eqir() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->read(this->A) == this->registry[this->read(this->B)] ? 1 : 0;
		registry[this->read(this->C)] = this->read(this->A) == this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}

	bool Instruction::eqri() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] == this->read(this->B) ? 1 : 0;
		registry[this->read(this->C)] = this->before[this->read(this->A)] == this->read(this->B) ? 1 : 0;
		return this->after == registry;
	}

	bool Instruction::eqrr() {
		auto registry = this->before;
		this->registry[this->read(this->C)] = this->registry[this->read(this->A)] == this->registry[this->read(this->B)] ? 1 : 0;
		registry[this->read(this->C)] = this->before[this->read(this->A)] == this->before[this->read(this->B)] ? 1 : 0;
		return this->after == registry;
	}

	void Instruction::setOperation(vector<int> operation) {
		this->operation = operation;
	}

	int Instruction::read(const int registry) {
		return this->operation[registry];
	}

	int Instruction::operationCode() {
		return this->operation[this->OPCODE];
	}

	int Instruction::readRegistry(int registry) {
		return this->registry[registry];
	}

	void Instruction::run() {
		switch (this->operationCode()) {
		case 0:
			this->muli();
			break;
		case 1:
			this->seti();
			break;
		case 2:
			this->bani();
			break;
		case 3:
			this->gtri();
			break;
		case 4:
			this->gtrr();
			break;
		case 5:
			this->eqrr();
			break;
		case 6:
			this->addi();
			break;
		case 7:
			this->gtir();
			break;
		case 8:
			this->eqir();
			break;
		case 9:
			this->mulr();
			break;
		case 10:
			this->addr();
			break;
		case 11:
			this->borr();
			break;
		case 12:
			this->bori();
			break;
		case 13:
			this->eqri();
			break;
		case 14:
			this->banr();
			break;
		case 15:
			this->setr();
			break;
		}
	}

	int Part1(vector<Instruction> instructions) {
		int total = 0;
		map<string, vector<int>> log;
		for (auto &instruction : instructions) {
			int run = 0;
			if (instruction.addr()) {
				log["addr"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.addi()) {
				log["addi"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.mulr()) {
				log["mulr"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.muli()) {
				log["muli"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.banr()) {
				log["banr"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.bani()) {
				log["bani"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.borr()) {
				log["borr"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.bori()) {
				log["bori"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.setr()) {
				log["setr"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.seti()) {
				log["seti"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.gtir()) {
				log["gtir"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.gtri()) {
				log["gtri"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.gtrr()) {
				log["gtrr"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.eqir()) {
				log["eqir"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.eqri()) {
				log["eqri"].push_back(instruction.operationCode());
				run++;
			}
			if (instruction.eqrr()) {
				log["eqrr"].push_back(instruction.operationCode());
				run++;
			}
			if (run >= 3) {
				total++;
			}
		}
		return total;
	}

	int Part2(vector<vector<int>> operations) {
		vector<int> dummy = { 0,0,0,0 };
		auto instruction = Instruction(dummy, dummy, dummy);
		for (auto &operation : operations) {
			instruction.setOperation(operation);
			instruction.run();
		}
		return instruction.readRegistry(0);
	}
}
