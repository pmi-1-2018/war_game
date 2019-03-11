#pragma once
#include <iostream>
using namespace std;

class Unit
{
protected:
	int damage = -1;
	int defense = -1;
	int healthPoints = -1;
public:
	int GetDefense() { return defense; }
	int GetDamage() { return damage; }
	int GetHealthPoints() { return healthPoints; }
	virtual int DamageTaken() { return 0; }

	void SetDamage(int new_damage){ damage = new_damage; }
	void SetHealthPoints(int new_healthPoints) { healthPoints = new_healthPoints; }

	virtual void attack(Unit& unit) {};
	
};

