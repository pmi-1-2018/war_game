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

};