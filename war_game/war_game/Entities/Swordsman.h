#pragma once

#include "Unit.h"

class Swordsman : public Unit
{

public:
	Swordsman()
	{
		damage = 25;
		defense = 1;
		healthPoints = 60;
		maxHP = 60;
		id = 1;
	}
	/*
	ostream& output(ostream&out) override {
		out << 'S';
		return out;
	}
	*/

};
