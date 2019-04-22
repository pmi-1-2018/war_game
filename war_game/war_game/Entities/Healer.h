#pragma once

#include "Unit.h"

class Healer : public Unit
{
public:
	Healer()
	{
		cost = 80;
		damage = 10;
		healthPoints = 60;
		defense = 2;
		maxHP = 60;
		dec_energy = -1;
		id = 6;
		symb = 'H';
	}
	void Heal(Unit& other_unit) override;
};