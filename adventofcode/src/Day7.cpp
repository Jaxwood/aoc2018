#include "Day7.h"

using namespace std;

namespace Day7 {

	string Part1(vector<tuple<string, string>> tokens) {
		Sleigh sleigh = Sleigh(tokens);
		while (sleigh.moreMoves())
		{
			auto moves = sleigh.move();
			sleigh.accept(moves[0]);
		}
		return sleigh.path();
	}

	int Part2(vector<tuple<string, string>> tokens, int elves) {
		WorkerPool pool = WorkerPool(tokens, elves);
		Sleigh sleigh = Sleigh(tokens);
		while (sleigh.moreMoves())
		{
			auto moves = sleigh.move();
			auto accepted = pool.assignWork(moves);
			for(auto &accept : accepted) {
				sleigh.accept(accept);
			}
			pool.tick();
		}
		pool.wait();
		auto path = sleigh.path();
		return pool.time();
	}
}
