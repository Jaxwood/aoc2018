#pragma once

#include <vector>

namespace Day3 {

	class Fabric {

	private:
		int _height;
		int _width;
		int _left;
		int _top;

	public:
		Fabric(int left, int top, int width, int height) {
			_height = height;
			_width = width;
			_top = top;
			_left = left;
		};

		int top() {
			return _top;
		}

		int bottom() {
			return _top + _height;
		}

		int left() {
			return _left;
		}

		int right() {
			return _left + _width;
		}
	};

	int Part1(std::vector<Fabric> tokens);
}
