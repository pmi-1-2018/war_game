
#pragma once

#include "Unit.h"

class Archer : public Unit
{
public:
	Archer()
	{
		cost = 110;
		damage = 30;
		defense = 5;
		healthPoints = 110;
		maxHP = 60;
		dec_energy = -1;
		id = 2;
		symb = 'A';
	}
};