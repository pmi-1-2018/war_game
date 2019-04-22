#pragma once

#include "Unit.h"

class Wizard : public Unit
{

public:
	Wizard()
	{
		cost = 100;
		damage = 32;
		defense = 1;
		healthPoints = 50;
		maxHP = 50;
		dec_energy = -2;
		id = 4;
		symb = 'W';
	}
};
