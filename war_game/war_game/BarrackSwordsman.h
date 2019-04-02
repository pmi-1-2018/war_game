#pragma once
#include"Entities/Barrack.h"

class BarrackSwordsman: public Barrack
{
public:
	BarrackSwordsman()
	{
		numberOfUnits = 10;
	}
	Unit* giveUnits()
	{
		cout << "how many swordsmen do you want to take?" << endl;
		int n;
		cin >> n;
		if (n <= GetNumberOfUnits() && n > 0)
		{
			Unit* units = new Swordsman[n];
			return units;
		}
		else
		{
			cout << "There is no such number of swordsmen" << endl;
		}
	}
};