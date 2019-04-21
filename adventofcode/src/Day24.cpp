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

	void AttackPlan::targetOrder() {
		sort(begin(this->groups), end(this->groups), [](Group &g1, Group &g2){
			if (g1.effectivePower() == g2.effectivePower()) {
				return g1.combatInitiative() < g2.combatInitiative();
			}
			return g1.effectivePower() < g2.effectivePower();
		});
	}

	bool AttackPlan::sideIsAlive(Side side) {
		return count_if(begin(this->groups), end(this->groups), [side](Group &g) {
			return g.side() == side && g.isAlive();
		}) > 0;
	}

	bool AttackPlan::sideHasWon() {
		return this->sideIsAlive(Defense) && this->sideIsAlive(Attack);
	}

	int AttackPlan::result() {
		if (!this->sideHasWon()) {
			throw exception("no side has won");
		}

		if (this->sideIsAlive(Defense)) {
			return accumulate(begin(this->groups), end(this->groups), 0, [](int acc, Group &g) {
				return g.isAlive() && g.side() == Defense ? acc += g.units() : acc;
			});
		}
		else {
			return accumulate(begin(this->groups), end(this->groups), 0, [](int acc, Group &g) {
				return g.isAlive() && g.side() == Attack ? acc += g.units() : acc;
			});
		}
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
