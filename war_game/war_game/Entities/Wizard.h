#pragma once

#include "Unit.h"

class Wizard : public Unit
{

public:
	Wizard()
	{
		damage = 32;
		defence = 1;
		healthPoints = 50;
		maxHP = 50;
		dec_energy = -2;
		id = 4;
		symb = 'W';
	}
};
