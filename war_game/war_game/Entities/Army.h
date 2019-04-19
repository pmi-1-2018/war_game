#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <typeinfo>
#include "Unit.h"
#include "Swordsman.h"
#include "Tank.h"
#include "Archer.h"
#include "Buffer.h"
#include "Healer.h"
#include "Wizard.h"

using namespace std;

static int counter = 0;
class Army
{
private:
	string nameOfArmy;
	vector<Unit> units;
	vector<Unit>::iterator it;
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
	Army(string name,vector<Unit> list, char symb, bool isPlayer);

	void inputTheArmy();
	void printArmiesFight(Army& a, int& incomingMagic, int& outcomingMagic, int& incomingDamage, int& outcomingDamage);
	void printArmy();

	void fight(Army& a,bool check);
	bool armyAutoAttack(Army& a);
	bool battlePVE(Army& a);
	bool battlePVP(Army& a);

	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	void setIsBotArmy(bool value);

	Army& operator= (const Army& army);
	vector<Unit> getUnits();
	void CalcLevelAndCapacity(int countOfDead);
	void addUnit(Unit unit);

	void swapUnits_2(int & index1, int & index2, Army& army1);
	void swapUnits_1(int & index1, int & index2, Army& army2);
	void swapUnits();

	char GetSymb();
	int GetId();
	bool SetCurrEnergy(const int& value);
	int GetCurrEnergy();
	int GetLevel();
	int GetExp();
	void SetLevel(int a);
	void SetCapacity(int a);
	int GetCapacity();
	int getNumberOfUnits();
};
