#include "Day5.h"

#include <cctype>
#include <string>

namespace Day5 {

	int Part1(std::string input) {

		for (int i = 0; i < input.size(); i++) {
			if (std::isupper(input[i]))
			{
				if (input[i+1] == std::tolower(input[i]))
				{
					return Part1(input.erase(i, 2));
				}
			}
			else
			{
				if (input[i+1] == std::toupper(input[i]))
				{
					return Part1(input.erase(i, 2));
				}
			}
		}

		return input.size();
	}
}
