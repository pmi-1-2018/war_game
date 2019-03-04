#pragma once
#include "Unit(2).h"
#include <iostream>
using namespace std;

class Swordsman : public Unit
{

public:
	Swordsman() 
	{ 
		damage = 25;
		defense = 1;
		healthPoints = 60;
	}

	void attack(Unit& otherUnit)
	{	
			otherUnit.SetHealthPoints(
				otherUnit.GetHealthPoints() - this->GetDamage() + otherUnit.GetDefense()
			);	
	}
	int DamageTaken()
	{
		int damageTaken = 60 - GetHealthPoints();
		return damageTaken;
	}
};
