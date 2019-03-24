#include "Unit.h"

Unit::Unit() : damage(0), defense(0), healthPoints(0), maxHP(0), id(0) {}
Unit::Unit(int dmg, int def, int hp, int maxHPe, int ide) {
	damage = dmg;
	defense = def;
	healthPoints = hp;
	maxHP = maxHPe;
	id = ide;
}

int Unit::GetDefense()
{
	return defense;
}

int Unit::GetDamage()
{
	return damage;
}

int Unit::getId() {
	return id;
}

char Unit::getSymb()
{
	return symb;
}

int Unit::GetHealthPoints()
{
	return healthPoints;
}

void Unit::SetDamage(int new_damage)
{
	damage = new_damage;
}

void Unit::SetDefense(int new_defense)
{
	defense = new_defense;
}

void Unit::SetHealthPoints(int new_healthPoints)
{
	healthPoints = new_healthPoints;
}

void Unit::attack(Unit& otherUnit)
{
	otherUnit.SetHealthPoints(
		otherUnit.GetHealthPoints() - this->GetDamage() + otherUnit.GetDefense()
	);
};

int Unit::DamageTaken()
{
	int damageTaken = maxHP - GetHealthPoints();
	return damageTaken;
}



ostream& operator<<(ostream &os, Unit &unit) {
	os << unit.getSymb();
	return os;
}

