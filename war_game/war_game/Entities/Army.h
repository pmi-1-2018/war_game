#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "Windows.h"
#include "Unit.h"
#include "../Entities/Swordsman.h"
#include "../Entities/Tank.h"
#include "Archer.h"

using namespace std;

class Artefact 
{
public:
	char symb;
	int invPosX;
	int invPosY;
	bool isActive;
	bool isSelected;
	Artefact() 
	{
		this->isSelected = false;
		this->symb = '-';
		isActive = false;
	}

	Artefact(char symb, int invPosX, int invPosY, bool isActive) 
		:symb(symb), 
		invPosX(invPosX), 
		invPosY(invPosY),
		isActive(isActive)
	{
		this->isSelected = false;
	}
};

static int counter = 0;
class Army
{
private:
	string nameOfArmy;
	Unit *units = nullptr;
	int numberOfUnits;
	char symb;
	int id;
	static const int START_ENERGY = 11;
	int dec_energy = 0;
	int currentEnergy;
	bool isPlayer = false;
	bool isBotArmy = false;
	int wallet;
	int income = 0;
	int stashSize = 2;
	int inventoryWidth = 3;
	int inventoryHeight = 3;
	vector<Artefact> artefacts;
	const HANDLE HSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	Army();
	Army(string name, Unit*list, int num, char symb, bool isPlayer, int money);
	void inputTheArmy();
	void printArmiesFight(Army& a, int thisArmy, int otherArmy, int incomingDamage, int outcomingDamage);
	void printArmies(Army& a, int thisArmy, int otherArmy);
	void printArmy();
	bool armyAutoAttack(Army& a);
	bool battlePVE(Army& a);
	bool battlePVP(Army& a);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	int getWallet();
	int getIncome();
	void setIsBotArmy(bool value);
	void increaseIncome(int value);
	void addMoneyToWallet(int value);
	Army& operator= (const Army& army);
	int getNumber();
	Unit* getWarriors();
	bool isDead(Unit unit);
	char GetSymb();
	int GetId();
	int getNumberOfUnits();
	void armyMove(Unit*list, int number);
	void addUnit(Unit unit);
	void swapUnits_2(int & index1, int & index2, Army& army1, int alive_count_army1, int alive_count_army2);
	void swapUnits_1(int & index1, int & index2, Army& army2, int alive_count_army1, int alive_count_army2);
	bool SetCurrEnergy(const int& value);
	int GetCurrEnergy();
	void PrintInventory(int& selectedX, int& selectedY, bool selectedFirst, int& artIndex);
	void SwapArtefact(int& artIndex1, int& artIndex2);
	void InventoryMode();
	~Army()
	{
		if (this->units != nullptr) 
		{
			delete[] this->units;
		}
	}
};