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

	Side toSide(string side) {
		if (side == "Immune System") {
			return Defense;
		}
		if (side == "Infection") {
			return Attack;
		}
		throw exception("unknown side");
	}

	int Part1(vector<Group> armies) {
		auto plan = AttackPlan(armies);

		while (!plan.sideHasWon()) {
			// target selection
			plan.targetOrder();
			plan.selectTargets();

			// attacking
			plan.executePlan();
		}

		return plan.result();
	}
}
