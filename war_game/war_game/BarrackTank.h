#pragma once
#include"Entities/Barrack.h"

class BarrackTank : public Barrack
{
public:
	BarrackTank()
	{
		numberOfUnits = 4;
	}
	Unit* giveUnits()
	{
		cout << "how many tanks do you want to take?" << endl;
		int n;
		cin >> n;
		if (n <= GetNumberOfUnits() && n > 0)
		{
			Unit* units = new Tank[n];
			return units;
		}
		else
		{
			cout << "There is no such number of tanks" << endl;
		}
	}
};