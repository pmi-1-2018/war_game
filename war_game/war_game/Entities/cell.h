#pragma once
#include"Barrack.h"
#include "BarrackArcher.h" 
#include"BarrackSwordsman.h"
#include"BarrackTank.h"
#include"BarrackWizard.h"
#include"BarrackBuffer.h"
#include"BarrackHealer.h"
#include "Army.h"
#include"GoldMine.h"
#include "Castle.h"
//static int counter = 0;

class Cell
{
private:
	int passCost;
	bool isPassable;
	Barrack* barrack;
	GoldMine* goldMine;
	Castle* castle;
	bool isCastle = false;
	bool isBarrack = false;
	Army* army = nullptr;
	int x;
	int y;
	int playersCount = 1;

public:
	Cell();
	Cell(const Cell& other);
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
	bool isPassableGenerate() {
		return this->army == nullptr && this->barrack == nullptr && this->castle == nullptr && this->isPassable;
	}
	void setPassCost(int value);
	void setIsBotArmy(bool value);
	int GetX()const;
	int GetY()const;
	Army* getArmyPtr()const;
	Barrack* getBarrackPtr();
	Castle* getCastlePtr();
	bool IsBarrack();
	bool IsCastle();
	Army* getArmyPtr();
	bool isPossibleGenerate();
	GoldMine* getGoldMinePtr();
	~Cell();
	friend ostream&operator<<(ostream& os, const Cell &c) {
		os << "(" << c.x << ":" << c.y << ")";
		return os;
	}
};

