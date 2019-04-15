#pragma once
#include"Barrack.h"
#include "BarrackArcher.h" 
#include"BarrackSwordsman.h"
#include"BarrackTank.h"
#include"BarrackWizard.h"
#include "Army.h"

//static int counter = 0;

class Cell
{
private:
	int passCost;
	bool isPassable;
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
	void SetPlayer(Army* army);
	void SetBattleField(Army* players, const int& size);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	char GetArmySign();
	int GetArmyId();
	void SetArmy(Army* army);
	Army* GetArmy()const;
	bool IsPassable();
	void setPassCost(int value);
	void setIsBotArmy(bool value);
	int GetX()const;
	int GetY()const;
	Army* getArmyPtr()const;
	Barrack* getBarrackPtr();
	bool IsBarrack();
	Army* getArmyPtr();
	~Cell();
	friend ostream&operator<<(ostream& os, const Cell &c) {
		os << "(" << c.x << ":" << c.y << ")";
		return os;
	}
};

