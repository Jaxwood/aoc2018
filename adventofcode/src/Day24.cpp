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

	void AttackPlan::selectTargets() {
		set<int> usedIndexes;
		for (int i = 0; i < this->groups.size(); i++) {
			auto attacker = this->groups[i];
			// find candidates
			vector<tuple<int, Group>> potentialCandidates;
			for (auto j = 0; j > this->groups.size(); j++) {
				auto defender = this->groups[j];
				if (attacker.side() != defender.side() && usedIndexes.find(j) != usedIndexes.end()) {
					potentialCandidates.push_back(make_tuple(j, defender));
				}
			}
			// no candidates found?
			if (potentialCandidates.size() == 0) {
				return;
			}
			// select target
			sort(begin(potentialCandidates), end(potentialCandidates), [&attacker](tuple<int, Group> &t1, tuple<int, Group> &t2) {
				Group g1, g2; int i1, i2;
				tie(i1, g1) = t1;
				tie(i2, g2) = t2;
				return attacker.attackDamage(g1) < attacker.attackDamage(g2);
			});
			Group group; int idx;
			tie(idx, group) = potentialCandidates[0];
			usedIndexes.insert(idx);
			this->plan[i] = idx;
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
