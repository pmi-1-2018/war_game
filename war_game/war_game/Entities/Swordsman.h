#pragma once

#include "Unit.h"

class Swordsman : public Unit
{

public:
	Swordsman()
	{
		damage = 25;
		defence = 1;
		healthPoints = 60;
		maxHP = 60;
		dec_energy = -2;
		id = 1;
		symb = 'S';
	}
};
