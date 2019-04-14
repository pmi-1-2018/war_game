#pragma once

#include "Unit.h"

class Wizard : public Unit
{
public:
	Wizard()
	{
		damage = 15;
		healthPoints = 60;
		defense = 1;
		maxHP = 60;
		dec_energy = -1;
		id = 4;
	}
	/*void BuffDamage(Unit other_unit) override;
	void BuffDefense(Unit other_unit) override;
	void Heal(Unit other_unit) override;*/
};