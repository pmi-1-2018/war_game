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
	Army *pointerToOwner;
public:
	GoldMine();
	void increaseLvl(int& vallet);
	int getIncome();
	char getOwner();
	int getLvl();
	Army* getPointerToOwner();
	void setPointerToOwner(Army* player);
	void giveGold(int& vallet);
	void setOwner(char newOwnerSymb);
};