#pragma once
#include "Barrack.h"
#include "GoldMine.h"
class Castle {
private:
	string nameOfArmy;
	GoldMine goldMine;
	int health;
	Barrack* barrack;
public:
	Barrack* getBarrack();
	void setBarrack(int n);
	int getHealth();
	string getNameOfArmy();
	void setGoldMine();
	// todo: realization of fighting in castle
	void fight();
};