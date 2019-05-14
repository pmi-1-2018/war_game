#pragma once
#include "Barrack.h"
#include "GoldMine.h"
#include "Army.h"
class Castle {
private:
	string nameOfArmy;
	GoldMine goldMine;
	int health;
	Barrack* barrack;
	Army* pointerToOwner;
	void setPointerToOwnerOfGoldMine();
public:
	Barrack* getBarrack();
	void setBarrack(int n);
	int getHealth();
	string getNameOfArmy();
	void setGoldMine();
	void setPointerToOwner(Army* player);
	// todo: realization of fighting in castle
	void fight();
};