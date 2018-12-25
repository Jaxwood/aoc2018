#include "Day13.h"

namespace Day13 {


	tuple<int, int> Part1(vector<string> lines) {
		auto network = Network(lines);
		network.setup();
		while (network.tick());
		return network.collesion();
	}

	tuple<int, int> Part2(vector<string> lines) {
		auto network = Network(lines);
		network.setup();
		while (network.crashes());
		return network.lastCart();
	}

	bool operator==(const Cart &c1, const Cart &c2) {
		return c1.position() == c2.position();
	}
}
