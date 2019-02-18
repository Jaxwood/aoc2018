#include <map>
#include <tuple>

namespace Day22 {
	enum ErosionLevel {
		Rocky = 0,
		Wet = 1,
		Narrow = 2
	};

	int Part1(std::tuple<int, int> target, int depth);
}
