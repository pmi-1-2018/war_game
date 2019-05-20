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
#include"Artifact.h"
class Cell
{
private:
	int passCost;
	bool isPassable;
	Barrack* barrack;
	GoldMine* goldMine;
	bool isBarrack = false;
	Army* army = nullptr;
	Artifact* artifact;
	Bonus* bonus;
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
	Artifact* getArifactPtr();
	Bonus * getBonusPtr();
	void setArtifactPtr(Artifact* artif);
	bool IsPassable();
	bool isPassableGenerate() {
		return this->army == nullptr && this->barrack == nullptr && this->isPassable;
	}
	void setPassCost(int value);
	void setIsBotArmy(bool value);
	int GetX()const;
	int GetY()const;
	Army* getArmyPtr()const;
	Barrack* getBarrackPtr();
	bool IsBarrack();
	Army* getArmyPtr();
	bool isPossibleGenerate();
	GoldMine* getGoldMinePtr();
	void setBonusPtr(Bonus * bonus);
	~Cell();
	friend ostream&operator<<(ostream& os, const Cell &c) {
		os << "(" << c.x << ":" << c.y << ")";
		return os;
	}
};

