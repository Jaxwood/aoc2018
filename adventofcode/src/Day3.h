#pragma once

#include <vector>

namespace Day3 {

	class Fabric {

	private:
		int _x;
		int _y;
		int _w;
		int _h;

	public:
		Fabric(int w, int h, int x, int y) {
			_x = x;
			_y = y;
			_h = h;
			_w = w;
		};

		int getWidth() {
			return _w;
		}

		int getHeight() {
			return _h;
		}

		int getX() {
			return _x;
		}

		int getY() {
			return _y;
		}
	};

	int Part1(std::vector<Fabric> tokens);
}
