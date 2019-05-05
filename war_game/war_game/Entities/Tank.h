#pragma once

#include "Unit.h"

class Tank : public Unit
{
public:
	Tank()
	{
		damage = 15;
		healthPoints = 90;
		defense = 7;
		maxHP = 90;
		dec_energy = -3;
		id = 3;
		symb = 'T';
	}
};