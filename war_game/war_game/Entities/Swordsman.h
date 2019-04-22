#pragma once

#include "Unit.h"

class Swordsman : public Unit
{

public:
	Swordsman()
	{
		cost = 60;
		damage = 25;
		defense = 0;
		healthPoints = 80;
		maxHP = 75;
		dec_energy = -2;
		id = 1;
		symb = 'S';
	}
};
