#pragma once
#include"Unit(2).h"

class Tank : public Unit
{
public:
	Tank()
	{
		damage = 15;
		healthPoints = 100;
		defense = 5;
	}

	void attack(Unit& otherUnit)
	{
		otherUnit.SetHealthPoints(
				otherUnit.GetHealthPoints() - this->GetDamage() + otherUnit.GetDefense()
			);
	}
	int DamageTaken()
	{
		int damageTaken = 100 - GetHealthPoints();
		return damageTaken;
	}
};
