#pragma once
#include "Barrack.h"

class BarrackArcher : public Barrack
{
public:
	BarrackArcher()
	{
		numberOfUnits = 7;
	}
	Unit giveUnit()
	{
		Archer unit;
		return unit;
	}
	string TellType()
	{
		return "barrack of archers";
	}
	int getCost()
	{
		Archer unit;
		return unit.getCost();
	}

};