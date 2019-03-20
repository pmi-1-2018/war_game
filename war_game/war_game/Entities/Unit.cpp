#include "Unit.h"

int Unit:: GetDefense()
{
	return defense;
}

int Unit:: GetDamage()
{ 
	return damage; 
}

int Unit:: GetHealthPoints() 
{ 
	return healthPoints; 
}

void Unit:: SetDamage(int new_damage)
{
	damage = new_damage;
}

void Unit:: SetDefense(int new_defense) 
{
	defense = new_defense;
}

void Unit:: SetHealthPoints(int new_healthPoints)
{ 
	healthPoints = new_healthPoints; 
}

void Unit:: attack(Unit& otherUnit) 
{
	otherUnit.SetHealthPoints(
		otherUnit.GetHealthPoints() - this->GetDamage() + otherUnit.GetDefense()
	);
};

 int Unit:: DamageTaken()
{
	int damageTaken = maxHP - GetHealthPoints();
	return damageTaken;
}
