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
	int wallet;
	int income = 0;
	int level;
	int experience;
	int capacity;
public:
	Army();
	Army(string name,vector<Unit> list, char symb, bool isPlayer, int wallet);

	void inputTheArmy();
	void printArmiesFight(Army& a, int& incomingDamage, int& outcomingDamage, int& incomingMagic, int& outcomingMagic);
	void printArmy();

	void fight(Army& a,bool check);
	bool armyAutoAttack(Army& a);
	bool battlePVE(Army& a);
	bool battlePVP(Army& a);
	void heal();
	void buff();

	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	int getWallet();
	int getIncome();
	void setIsBotArmy(bool value);
	void increaseIncome(int value);
	void addMoneyToWallet(int value);


	Army& operator= (const Army& army);
	vector<Unit> getUnits();
	void CalcLevelAndCapacity(int countOfDead);
	void addUnit(Unit unit);

	void swapUnits_2(int & index1, int & index2, Army& army1);
	void swapUnits_1(int & index1, int & index2, Army& army2);
	void swapUnits(int& index1, int& index2);
	void ArmySwap(int& index1, int& index2);

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
