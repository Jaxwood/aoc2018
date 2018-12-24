#include "Day13.h"

namespace Day13 {


	tuple<int, int> Part1(vector<string> lines) {
		auto network = Network(lines);
		network.setup();
		while (network.tick()) {}
		return network.collesion();
	}
}
