#include "Day5.h"

#include <cctype>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

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

	std::string RemoveChars(std::string input, char c)
	{
		int i = 0;
		while(i < input.size())
		{
			if (input[i] == c || input[i] == std::toupper(c))
			{
				input = input.erase(i, 1);
			}
			else
			{
				i++;
			}
		}

		return input;
	}

	int Part2(std::string input)
	{
		// get all uniques
		std::set<char> chars;
		for (int i = 0; i < input.size(); i++)
		{
			chars.insert(std::tolower(input[i]));
		}

		// candidates
		std::vector<int> candidates;
		for (char it : chars)
		{
			candidates.push_back(Part1(RemoveChars(input, it)));
		}


		// reduce
		return *std::min_element(candidates.begin(), candidates.end());
	}
}
