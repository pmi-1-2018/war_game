#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
//#include "Unit.h"
//#include "Archer.h"

using namespace std;

class Unit {
private:
	int dmg;
	int health;
	int defense;
public:
	int GetDamage() {
		return dmg;
	}
	int GetHealthPoints() {
		return health;
	}
	void SetHealthPoints(int hp) {
		health = hp;
	}
	int GetDefense() {
		return defense;
	}

};

class Archer {

};

static int counter = 0;
class Army
{
private:
	string nameOfArmy;
	Unit *units;
	int numberOfUnits;
	char symb;
	int id;
public:
	Army();
	Army(string name, Unit*list, int num, char symb);
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

	//armyMove
};