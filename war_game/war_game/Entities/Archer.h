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
		maxHP = 50;
		dec_energy = -1;
	}
};
