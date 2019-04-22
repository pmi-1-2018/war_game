#pragma once

#include "Unit.h"

class Buffer : public Unit
{
public:
	Buffer()
	{
		cost = 100;
		damage = 7;
		healthPoints = 40;
		defense = 1;
		maxHP = 40;
		dec_energy = -1;
		id = 5;
		symb = 'B';
	}
	static void BuffDamage(Unit& other_unit);
	static void BuffDefense(Unit& other_unit);
};