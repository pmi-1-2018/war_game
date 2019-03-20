#pragma once
#include"Barrack.h"
#include "../Entities/Army.h"

//static int counter = 0;

class Cell
{
private:
	int passCost;
	bool isPassable;
	bool isPlayer = false;
	Barrack* barrack;
	Army* army;
	int x;
	int y;

public:
	Cell();
	Cell(int passCost, int x, int y);	
	void setCell(char symb);
	int getPassCost();
	bool IsPlayer();
	void SetPlayer(bool val, char symb);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	char GetArmySign();
	int GetArmyId();
	bool IsPassable();
	void setPassCost(int value);
	Barrack* getBarrackPtr();

};

