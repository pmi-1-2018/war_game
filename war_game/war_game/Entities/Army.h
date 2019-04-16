#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include "Unit.h"
#include "Swordsman.h"
#include "Tank.h"
#include "Archer.h"
#include "Wizard.h"

using namespace std;

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
	int level;
	int experience;
	int capacity;
public:
	Army();
	Army(string name, Unit*list, int num, char symb, bool isPlayer);
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
	void setIsBotArmy(bool value);
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
	~Army()
	{
		if (this->units != nullptr) 
		{
			delete[] this->units;
		}
	}
	int GetLevel();
	int GetExp();
	void SetLevel(int a);
	void CalcLevelAndCapacity(int countOfDead);
	void SetCapacity(int a);
	int GetCapacity();
	bool CheckCapacity();
};