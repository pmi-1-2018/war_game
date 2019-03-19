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

class Army
{
private:
	string nameOfArmy;
	Unit *units;
	int numberOfUnits;
public:
	Army();
	Army(string name, Unit*list, int num);
	void armyAttack(Army a);
	friend istream&operator>>(istream&is, Army &army);
	void inputTheArmy(Army army);
	int getNumber();
	Unit *getWarriors();
	bool isDead(Unit unit);
	void armyMove(Unit*list, int number);
	void addUnit(Unit unit);

	//armyMove
};