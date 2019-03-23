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
	int playersCount = 1;

public:
	Cell();
	Cell(int passCost, int x, int y);	
	void setCell(char symb);
	int getPassCost();
	bool IsPlayer();
	void SetPlayer(bool val, Army* army);
	void SetBattleField(Army** players, const int& size);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	char GetArmySign();
	int GetArmyId();
	void SetArmy(Army* army);
	Army* GetArmy(int& size)const;
	bool IsPassable();
	void setPassCost(int value);
	int GetX()const;
	int GetY()const;
	Barrack* getBarrackPtr();

};

