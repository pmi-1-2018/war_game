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

void Unit::setSymb(char symb)
{
	this->symb = symb;
}

int Unit::GetHealthPoints()
{
	return healthPoints;
}

void Unit::SetDamage(int new_damage)
{
	damage = new_damage;
}

int Unit::GetMaxHP()
{
	return this->maxHP;
}

void Unit:: SetDefense(int new_defense) 
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (unit.healthPoints == unit.maxHP)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));

		os << unit.getSymb();
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	}
	else if (unit.healthPoints >= 10 && unit.healthPoints < unit.maxHP)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		os << unit.getSymb();
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	}
	else
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		os << unit.getSymb();
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	}
	return os;
}
int Unit::GetDecEnergy() const
{
	return this->dec_energy;
}

