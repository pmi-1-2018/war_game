#pragma once
#include"Barrack.h"

class BarrackSwordsman: public Barrack
{
public:
	BarrackSwordsman()
	{
		numberOfUnits = 10;
	}
	Unit giveUnit()
	{
		Swordsman unit;
		return unit;
	}
};