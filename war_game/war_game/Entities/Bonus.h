#pragma once
#include"Army.h"
using namespace std;

class Bonus
{
private:
	int Damage= rand() % 15 + 1;
	int Exp= rand() % 10 + 1;
	int HP= rand() % 20 + 1;
	int gold=rand() % 100 + 1;
	int bonusTime = -1;
	bool isUsed = false;
public:
	Bonus()
	{
	}
	void setBonTime(int i)
	{
		 bonusTime=i;
	}
	int getBonTime()
	{
		return bonusTime;
	}
	void delBonTime(int i)
	{
			if (bonusTime != 0 && isUsed==true)
				bonusTime -= i;
	
	}
	
	void BonusDamage(vector<Unit> &units)
	{
		vector<Unit>::iterator it;
		for ( it = units.begin(); it != units.end(); it++)
		{
			it->SetDamage(it->GetDamage()+Damage);
		}
		isUsed = true;
	}


	void BonusHP(vector<Unit> &units)
	{
		vector<Unit>::iterator it;
		for (it = units.begin(); it != units.end(); it++)
		{
			it->SetHealthPoints(it->GetHealthPoints()+HP);
		}
		isUsed = true;
	}
	void DelBonusDamage(vector<Unit> &units)
	{
		vector<Unit>::iterator it;
		for (it = units.begin(); it != units.end(); it++)
		{
			it->SetDamage(it->GetDamage() - Damage);
		}
		isUsed = false;
	}

	
	void DelBonusHP(vector<Unit> &units)
	{
		vector<Unit>::iterator it;
		for (it = units.begin(); it != units.end(); it++)
		{
			it->SetHealthPoints(it->GetHealthPoints() - HP);
		}
		isUsed = false;
	}
	int getBonusGold()
	{
		return gold;
	}
	int getBonusExp()
	{
		return Exp;
	}
	
};
