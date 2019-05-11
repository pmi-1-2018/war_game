#pragma once
#include "Entities/Barrack.h"
class Castle {
private:
	string nameOfArmy;
	int health;
	Barrack barrack;
public:
	Barrack getBarrack(string nameOfArmy);
	int getHealth();
	string getNameOfArmy();
	// todo: realization of fighting in castle
	void fight();
};