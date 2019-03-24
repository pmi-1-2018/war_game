#pragma once

#include <iostream>
using namespace std;

class Unit
{
protected:
	int damage = 0;
	int defense = 0;
	int healthPoints = 0;
	int maxHP = 0;
	int dec_energy = 0;
public:

	void SetDamage(int new_damage);
	void SetHealthPoints(int new_healthPoints);
	void SetDefense(int new_defense);

	int GetDefense();
	int GetDamage();
	int GetHealthPoints();

	void attack(Unit& unit);
	int DamageTaken();

	virtual void BuffDamage(Unit other_unit) {};
	virtual void BuffDefense(Unit other_unit) {};
	int GetDecEnergy()const;
};
