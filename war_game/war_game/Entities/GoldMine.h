#pragma once
#include<iostream>
#include"Army.h"
class GoldMine
{
private:
	int level;
	char owner;
	int income;
	int maxLvl;
	int updateCost;
public:
	GoldMine();
	void increaseLvl(int& vallet);
	int getIncome();
	int getOwner();
	int getLvl();
	void giveGold(int& vallet);
	void setOwner(char newOwnerSymb);
};