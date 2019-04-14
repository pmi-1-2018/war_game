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
};