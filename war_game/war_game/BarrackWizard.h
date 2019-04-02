#pragma once
#include"Entities/Barrack.h"

class BarrackWizard : public Barrack
{
public:
	BarrackWizard()
	{
		numberOfUnits = 5;
	}
	Unit* giveUnits()
	{
		cout << "how many wizards do you want to take?" << endl;
		int n;
		cin >> n;
		if (n <= GetNumberOfUnits() && n > 0)
		{
			Unit* units = new Wizard[n];
			return units;
		}
		else
		{
			cout << "There is no such number of wizards" << endl;
		}
	}
};