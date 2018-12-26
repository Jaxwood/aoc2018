#include "Day14.h"

using namespace std;

namespace Day14 {

	Elv::Elv(int idx, int offset) {
		this->idx = idx;
		this->offset = offset;
	}

	int Elv::getIndex() {
		return this->idx;
	}

	int Elv::getOffset() {
		return this->offset;
	}

	void Elv::setNextIndex(int index) {
		this->idx = index;
	}

	void Elv::updateOffset(int size) {
		auto total = this->offset + this->idx;
		this->offset = total % size;
	}

	Reciepe::Reciepe(string initial) {
		this->reciepes = initial;
	}

	vector<Elv> Reciepe::produce(vector<Elv> elves) {
		int sum = 0;
		for (auto &elv : elves) {
			auto idx = elv.getOffset();
			auto num = this->reciepes[idx] - '0';
			sum += num;
			elv.setNextIndex(num + 1);
		}
		this->reciepes += to_string(sum);
		int size = this->reciepes.size();
		for (auto &elv : elves) {
			elv.updateOffset(size);
		}
		return elves;
	}

	int Reciepe::size() {
		return this->reciepes.size();
	}

	string Reciepe::result(int count) {
		return this->reciepes.substr(count, 10);
	}

	string Part1(int count) {
		vector<Elv> elves = { Elv(0, 0), Elv(1, 1) };
		auto reciepe = Reciepe("37");
		while(reciepe.size() < count + 10) {
			elves = reciepe.produce(elves);
		}
		return reciepe.result(count);
	}
}
