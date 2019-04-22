#pragma once

#include "Unit.h"

class Healer : public Unit
{
public:
	Healer()
	{
		cost = 100;
		damage = 5;
		healthPoints = 30;
		defense = 1;
		maxHP = 30;
		dec_energy = -1;
		id = 6;
		symb = 'H';
	}
	void Heal(Unit& other_unit) override;
};