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
	bool isBotArmy = false;
	Barrack* barrack;
	bool isBarrack = false;
	Army* army = nullptr;
	int x;
	int y;
	int playersCount = 1;

public:
	Cell();
	Cell(int passCost, int x, int y);
	void setCell(char symb, int x, int y);
	int getPassCost();
	bool IsPlayer();
	void SetPlayer(bool val, Army* army);
	void SetBattleField(Army* players, const int& size);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	char GetArmySign();
	int GetArmyId();
	void SetArmy(Army* army);
	Army* GetArmy(int& size)const;
	bool IsPassable();
	void setPassCost(int value);
	int GetX()const;
	int GetY()const;
	Barrack* getBarrackPtr();
	bool IsBarrack();
	Army* getArmyPtr();
	~Cell();
};

