#pragma once

#include <iostream>
#include "Windows.h"
using namespace std;

class Unit
{
protected:
	int cost = 0;
	int damage = 0;
	int defense = 0;
	int healthPoints = 0;
	int maxHP = 0;
	int id = 0;
	int dec_energy = 0;
	char symb = 'U';

public:
	Unit();
	Unit(int dmg, int def, int hp, int maxHPe, int ide);
	void SetDamage(int new_damage);
	void SetHealthPoints(int new_healthPoints);
	void SetDefense(int new_defense);

	int GetDefense();
	int GetDamage();
	int GetHealthPoints();
	int getId();
	char getSymb();
	void setSymb(char symb);
	int getCost();

	void attack(Unit& unit);
	int DamageTaken();
	virtual void BuffDamage(Unit& other_unit) {};
	virtual void BuffDefense(Unit& other_unit) {};
	virtual void Heal(Unit& other_unit) {};
	int GetMaxHP();
	int GetDecEnergy()const;
	//virtual ostream&output(ostream&out);
	friend ostream&operator<<(ostream&os, Unit &unit);
};