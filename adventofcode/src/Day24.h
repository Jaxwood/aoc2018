#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

namespace Day24 {

	typedef std::tuple<int, int> Index;

	enum DamageType {
		Fire = 0,
		Slashing = 1,
		Bludgeoning = 2,
		Radiation = 3,
		Cold = 4
	};

	enum Side {
		Defense = 0,
		Attack = 1
	};

	DamageType toDamageType(std::string typeToParse);
	Side toSide(std::string side);
	std::set<DamageType> toDamageTypes(std::vector<std::string> typesToParse);

	class Group {
	private:
		int unitCount;
		int hitpoints;
		int damage;
		int initiative;
		Side role;
		DamageType damageType;
		std::set<DamageType> immunities;
		std::set<DamageType> weaknesses;
		int hitpointPool() {
			return this->hitpoints * this->unitCount;
		}
		bool isImmune(Group group) {
			return this->immunities.find(group.damageType) != this->immunities.end();
		}
		bool isWeak(Group group) {
			return this->weaknesses.find(group.damageType) != this->weaknesses.end();
		}
	public:
		Group() {}

		Group(Side side, int unitCount, int hitpoints, std::set<DamageType> immunities, std::set<DamageType> weaknesses, int damage, DamageType damageType, int initiative) {
			this->role = side;
			this->unitCount = unitCount;
			this->hitpoints = hitpoints;
			this->immunities = immunities;
			this->weaknesses = weaknesses;
			this->damage = damage;
			this->damageType = damageType;
			this->initiative = initiative;
		}

		int effectivePower() {
			return this->unitCount * this->damage;
		}

		Side side() {
			return this->role;
		}

		int combatInitiative() {
			return this->initiative;
		}

		void takeDamage(Group group) {
			int amount = group.effectivePower();
			if (this->isWeak(group)) {
				amount *= 2;
			}
			if (this->isImmune(group)) {
				amount = 0;
			}
			this->unitCount -= (amount / this->hitpoints);
		}

		bool isAlive() {
			return this->hitpointPool() > 0;
		}

		int units() {
			return this->unitCount;
		}
		int attackDamage(Group &group);
	};

	class AttackPlan {
	private:
		std::map<int, int> plan;
		std::vector<Group> groups;
		bool sideIsAlive(Side side);
	public:
		AttackPlan(std::vector<Group> &groups) {
			this->groups = groups;
		}
		void targetOrder();
		void selectTargets();
		void executePlan();
		bool sideHasWon();
		int result();
	};

	int Part1(std::vector<Group> armies);
}
