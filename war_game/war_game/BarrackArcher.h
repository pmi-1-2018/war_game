#pragma once
#include"Entities/Barrack.h"

class BarrackArcher : public Barrack
{
public:
	BarrackArcher()
	{
		numberOfUnits = 7;
	}
	Unit* giveUnits() 
	{
		cout << "how many archers do you want to take?" << endl;
		int n;
		cin >> n;
		if (n <= GetNumberOfUnits() && n > 0)
		{
			Unit* units = new Archer[n];
			return units;
		}
		else
		{
			cout << "There is no such number of archers" << endl;
		}
	}

};