#include "Day24.h"

using namespace std;

namespace Day24 {

	DamageType toDamageType(string typeToParse) {
		if(typeToParse == "fire") {
			return Fire;
		}
		else if(typeToParse == "cold") {
			return Cold;
		}
		else if(typeToParse == "slashing") {
			return Slashing;
		}
		else if(typeToParse == "bludgeoning") {
			return Bludgeoning;
		}
		else if (typeToParse == "radiation") {
			return Radiation;
		}

		throw exception("unknown damage type");
	}

	set<DamageType> toDamageTypes(vector<string> typesToParse) {
		set<DamageType> result;
		transform(begin(typesToParse), end(typesToParse), inserter(result, result.begin()), toDamageType);
		return result;
	}

	int Part1(vector<Army> armies) {
		return 0;
	}

	void Army::addGroup(Group group) {
		this->groups.push_back(group);
	}
}
