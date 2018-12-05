#include "Day5.h"

#include <cctype>
#include <string>

namespace Day5 {

	int Part1(std::string input) {

		int i = 0;
		while (i < input.size())
		{
			if (std::isupper(input[i]))
			{
				if (input[i + 1] == std::tolower(input[i]))
				{
					input = input.erase(i, 2);
					i = 0;
				}
				else
				{
					i++;
				}
			}
			else
			{
				if (input[i + 1] == std::toupper(input[i]))
				{
					input = input.erase(i, 2);
					i = 0;
				}
				else
				{
					i++;
				}
			}
		}

		return input.size();
	}
}
