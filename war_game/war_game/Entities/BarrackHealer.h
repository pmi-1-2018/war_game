#pragma once
#include "Barrack.h"

class BarrackHealer : public Barrack
{
public:
	BarrackHealer()
	{
		numberOfUnits = 4;
	}
	Unit giveUnit()
	{
		Healer unit;
		return unit;
	}
	string TellType()
	{
		return "barrack of healers";
	}
	int getCost()
	{
		Healer unit;
		return unit.getCost();
	}

};