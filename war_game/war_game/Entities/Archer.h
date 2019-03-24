#pragma once

#include "Unit.h"

class Archer : public Unit
{
public:
	Archer()
	{
		damage = 20;
		defense = 1;
		healthPoints = 50;
		maxHP = 50;
		id = 2;
	}
	/*
	ostream&output(ostream&out) override {
		out << 'S';
		return out;
	}
	*/
	
};
