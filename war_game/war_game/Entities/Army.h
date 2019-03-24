#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include "Unit.h"
#include "Archer.h"

using namespace std;

static int counter = 0;
class Army
{
private:
	string nameOfArmy;
	Unit *units;
	int numberOfUnits = 5;
	char symb;
	int id;
public:
	Army();
	Army(string name, Unit*list, int num, char symb);
	//Army(const Army& army);
	void inputTheArmy();
	void printArmiesFight(Army a, int thisArmy, int otherArmy,int incomingDamage,int outcomingDamage);
	void printArmies(Army a, int thisArmy, int otherArmy);
	void printArmy();
	bool armyAutoAttack(Army a);
	bool battlePVE(Army a);
	bool battlePVP(Army a);
	//friend istream&operator<<(istream&is, Army &army);
	int getNumber();
	Unit getWarriors();
	bool isDead(Unit unit);
	char GetSymb();
	int GetId();
	void armyMove(Unit*list, int number);
	void addUnit(Unit unit);

	//armyMove
};