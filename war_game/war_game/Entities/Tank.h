#pragma once

#include "Unit.h"

class Tank : public Unit
{
public:
	Tank()
	{
		cost = 140;
		damage = 25;
		healthPoints = 100;
		defense = 8;
		maxHP = 100;
		dec_energy = -3;
		id = 3;
		symb = 'T';
	}
};