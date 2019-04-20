#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

namespace Day24 {

	enum DamageType {
		Fire = 0,
		Slashing = 1,
		Bludgeoning = 2,
		Radiation = 3,
		Cold = 4
	};

	DamageType toDamageType(std::string typeToParse);
	std::set<DamageType> toDamageTypes(std::vector<std::string> typesToParse);

	class Group {
	private:
		int unitCount;
		int hitpoints;
		int damage;
		int initiative;
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
		Group(int unitCount, int hitpoints, std::set<DamageType> immunities, std::set<DamageType> weaknesses, int damage, DamageType damageType, int initiative) {
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
	};

	class Army {
	private:
		std::vector<Group> groups;
		std::string type;
	public:
		Army(std::string type) {
			this->type = type;
		}

		void addGroup(Group group);
	};

	int Part1(std::vector<Army> armies);
}
