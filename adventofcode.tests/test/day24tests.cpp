#include "pch.h"

#include <fstream>
#include <algorithm>
#include <string>
#include <tuple>
#include <map>
#include <regex>
#include <iostream>
#include <sstream>

#include "Day24.h"

using namespace std;
using namespace Day24;

class day24Fixture : public ::testing::Test {

private:
	std::vector<std::string> _tokens;

public:
	void SetUp(std::string path) {
		std::vector<std::string> tokens;
		std::string line;
		std::ifstream stream;
		stream.open(path, std::iostream::in);
		while (std::getline(stream, line))
		{
			tokens.push_back(line);
		}

		if (stream.is_open())
		{
			stream.close();
		}

		_tokens = tokens;
	}

	std::vector<std::string> split(std::string strToSplit, char delimeter)
	{
		std::stringstream ss(strToSplit);
		std::string item;
		std::vector<std::string> splittedStrings;
		while (std::getline(ss, item, delimeter))
		{
			splittedStrings.push_back(item);
		}
		return splittedStrings;
	}

	vector<Group> getTokens() {
		auto result = vector<Group>();
		auto unitReg = regex("^(\\d+) units each with (\\d+) hit points (?:\\(?)(.+)?(?:\\)?)\\s?with an attack that does (\\d+) (\\w+) damage at initiative (\\d+)$", regex_constants::ECMAScript);
		auto armyTypeReg = regex("(Immune System|Infection):", regex_constants::ECMAScript);
		auto weaknessReg = regex("\\s?weak to (.*)", regex_constants::ECMAScript);
		auto immunitiesReg = regex("\\s?immune to (.*)", regex_constants::ECMAScript);
		auto dmgTypesReg = regex("\\b(slashing|fire|cold|radiation|bludgeoning)\\b");
		int idx = -1;
		string type;
		for (auto &token : _tokens) {
			smatch match;
			smatch immunitiesMatch;
			smatch weaknessMatch;
			smatch dmgTypesMatch;
			vector<string> weaknesses;
			vector<string> immunities;
			if (regex_match(token, match, armyTypeReg)) {
				type = match[1];
			}
			if (regex_match(token, match, unitReg)) {
				string defense = match[3];
				for (auto &s : split(defense, ';')) {
					if (regex_match(s, weaknessMatch, weaknessReg)) {
						string types = weaknessMatch[1];
						while (regex_search(types, dmgTypesMatch, dmgTypesReg)) {
							weaknesses.push_back(dmgTypesMatch[1]);
							types = dmgTypesMatch.suffix().str();
						}
					}
					if (regex_match(s, immunitiesMatch, immunitiesReg)) {
						string types = immunitiesMatch[1];
						while (regex_search(types, dmgTypesMatch, dmgTypesReg)) {
							immunities.push_back(dmgTypesMatch[1]);
							types = dmgTypesMatch.suffix().str();
						}
					}
				}
				auto group = Group(toSide(type), stoi(match[1]), stoi(match[2]), toDamageTypes(immunities), toDamageTypes(weaknesses), stoi(match[4]), toDamageType(match[5]), stoi(match[6]));
				result.push_back(group);
			}
		}
		return result;
	}
};

TEST_F(day24Fixture, Part1) {
	SetUp("part1.txt");
	auto actual = Day24::Part1(getTokens());
	EXPECT_EQ(5216, actual);
}
