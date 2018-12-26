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

	Reciepe::Reciepe(string initial, vector<int> target) {
		for (int i = 0; i < initial.size(); i++) {
			this->reciepes.push_back(initial[i] - '0');
		}
		this->target = target;
	}

	void Reciepe::produce(vector<Elv> &elves) {
		int sum = 0;
		for (auto &elv : elves) {
			auto idx = elv.getOffset();
			auto num = this->reciepes[idx];
			sum += num;
			elv.setNextIndex(num + 1);
		}
		auto str = to_string(sum);
		for (int i = 0; i < str.size(); i++) {
			this->reciepes.push_back(str[i] - '0');
		}
		int size = this->reciepes.size();
		for (auto &elv : elves) {
			elv.updateOffset(size);
		}
	}

	int Reciepe::size() {
		return this->reciepes.size();
	}

	int Reciepe::count() {
		auto it = search(begin(this->reciepes), end(this->reciepes), begin(target), end(target));
		return distance(begin(this->reciepes), it);
	}

	string Reciepe::result(int count, int length) {
		string result = "";
		for (int i = count; i < count + length; i++) {
			result += to_string(this->reciepes[i]);
		}
		return result;
	}

	bool Reciepe::match(vector<int> target) {
		return search(begin(this->reciepes), end(this->reciepes), begin(target), end(target)) != end(this->reciepes);
	}

	string Part1(int count) {
		vector<Elv> elves = { Elv(0, 0), Elv(1, 1) };
		auto reciepe = Reciepe("37", vector<int> { count });
		while(reciepe.size() < count + 10) {
			reciepe.produce(elves);
		}
		return reciepe.result(count, 10);
	}

	int Part2(vector<int> target) {
		vector<Elv> elves = { Elv(0, 0), Elv(1, 1) };
		auto reciepe = Reciepe("37", target);
		while (!reciepe.match(target)) {
			reciepe.produce(elves);
		}
		return reciepe.count();
	}
}
