#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include "../Entities/Unit.h"
#include "../Entities/Swordsman.h"
#include "../Entities/Tank.h"
#include "../Entities/Archer.h"

using namespace std;

static int counter = 0;
class Army
{
private:
	string nameOfArmy;
	Unit* units;
	int numberOfUnits;
	char symb;
	int id;
	static const int START_ENERGY = 10;
	int dec_energy = 0;
	int currentEnergy;
	int level;
	int experience;
	int capacity;
public:
	Army();
	Army(string name, Unit*list, int num, char symb);
	Army(const Army& army);
	void armyAttack(Army a);
	friend istream&operator>>(istream&is, Army &army);
	void inputTheArmy(Army army);
	int getNumber();
	Unit *getWarriors();
	bool isDead(Unit unit);
	char GetSymb();
	int GetId();
	void armyMove(Unit*list, int number);
	void addUnit(Unit unit);
	bool SetCurrEnergy(const int& value);
	int GetCurrEnergy();
	~Army();
	int GetLevel();
	int GetExp();
	void SetLevel(int a);
	void CalcLevelAndCapacity(int countOfDead);
	void SetCapacity(int a);
	bool CheckCapacity();
	//armyMove
};