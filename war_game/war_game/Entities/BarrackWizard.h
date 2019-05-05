#pragma once
#include"Barrack.h"

class BarrackWizard : public Barrack
{
public:
	BarrackWizard()
	{
		numberOfUnits = 5;
	}
	Unit giveUnit()
	{
		Wizard unit;
		return unit;
	}
	string TellType()
	{
		return "barrack of wizards";
	}
};