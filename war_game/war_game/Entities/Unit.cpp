#include "Unit.h"


Unit::Unit() : damage(0), defence(0), healthPoints(0), maxHP(0), id(0) {}
Unit::Unit(int dmg, int def, int hp, int maxHPe, int ide) {
	damage = dmg;
	defence = def;
	healthPoints = hp;
	maxHP = maxHPe;
	id = ide;
}

int Unit::calculateDamage(vector<Artifact> art)
{
	int returnDamage = 0;
	returnDamage += damage + damageBuff;
	for (size_t i = 0; i < art.size(); i++)
	{
		if (art[i].getId() == 1)
		{
			returnDamage += art[i].getAddPoints();
		}
	}
	return returnDamage;
}

int Unit::calculateDefence(vector<Artifact> art)
{
	int returnDefence = 0;
	returnDefence += defence + defenseBuff;
	for (size_t i = 0; i < art.size(); i++)
	{
		if (art[i].getId() == 2)
		{
			returnDefence += art[i].getAddPoints();
		}
	}
	return returnDefence;
}

int Unit::GetDefense()
{
	return defence;
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
	defence = new_defense;
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

