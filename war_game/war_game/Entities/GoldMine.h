#pragma once
#include<iostream>
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
};