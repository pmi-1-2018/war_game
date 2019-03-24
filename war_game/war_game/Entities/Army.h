#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include "../Entities/Unit.h"
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
	~Army();
	//armyMove
};