#pragma once
#include "Barrack.h"
class Castle {
private:
	string nameOfArmy;
	int health;
	Barrack* barrack;
public:
	Barrack* getBarrack(string nameOfArmy);
	void setBarrack(int n);
	int getHealth();
	string getNameOfArmy();
	// todo: realization of fighting in castle
	void fight();
};