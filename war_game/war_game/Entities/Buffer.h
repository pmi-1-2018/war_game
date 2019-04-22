#pragma once

#include "Unit.h"

class Buffer : public Unit
{
public:
	Buffer()
	{
		cost = 80;
		damage = 12;
		healthPoints = 80;
		defense = 2;
		maxHP = 80;
		dec_energy = -1;
		id = 5;
		symb = 'B';
	}
	static void BuffDamage(Unit& other_unit);
	static void BuffDefense(Unit& other_unit);
};