#pragma once

#include "Unit.h"

class Wizard : public Unit
{

public:
	Wizard()
	{
		cost = 180;
		damage = 30;
		defense = 4;
		healthPoints = 80;
		maxHP = 80;
		dec_energy = -2;
		id = 4;
		symb = 'W';
	}
};
