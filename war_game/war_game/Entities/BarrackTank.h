#pragma once
#include"Barrack.h"

class BarrackTank : public Barrack
{
public:
	BarrackTank()
	{
		numberOfUnits = 4;
	}
	
	Unit giveUnit()
	{
		Tank unit;
		return unit;
	}
	string TellType()
	{
		return "barrack of tanks";
	}
	int getCost()
	{
		Tank unit;
		return unit.getCost();
	}
};