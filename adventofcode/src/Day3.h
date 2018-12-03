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

		int getWidth() {
			return _width;
		}

		int getHeight() {
			return _height;
		}

		int getTop() {
			return _top;
		}

		int getLeft() {
			return _left;
		}
	};

	int Part1(std::vector<Fabric> tokens);
}
