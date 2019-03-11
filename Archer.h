#pragma once
#include "Unit.h"

class Archer : public Unit
{
public:
	Archer()
	{
		damage = 20;
		defense = 1;
		healthPoints = 50;
	}

	void attack(Unit& otherUnit)
	{
			otherUnit.SetHealthPoints(
				otherUnit.GetHealthPoints() - this->GetDamage() + otherUnit.GetDefense()
			);
	}
	int DamageTaken()
	{
		int damageTaken = 50 - GetHealthPoints();
		return damageTaken;
	}
};
