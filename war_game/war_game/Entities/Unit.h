#pragma once

#include "Artifact.h"
#include "Windows.h"
#include <iostream>
#include <vector>

using namespace std;

class Unit
{
protected:
	int damage = 0;
	int defence = 0;
	int healthPoints = 0;
	int maxHP = 0;
	int id = 0;
	int dec_energy = 0;
	char symb = 'U';
	int damageBuff = 0;
	int defenseBuff = 0;

public:
	Unit();
	Unit(int dmg, int def, int hp, int maxHPe, int ide);
	void SetDamage(int new_damage);
	void SetHealthPoints(int new_healthPoints);
	void SetDefense(int new_defense);

	int GetDefense();
	int GetDamage();
	int GetHealthPoints();
	int getDamageBuff();
	int getDefenseBuff();
	int getId();
	char getSymb();
	void setSymb(char symb);
	void setDamageBuff(int n);
	void setDefenseBuff(int n);

	int calculateDamage(vector<Artifact> art);
	int calculateDefence(vector<Artifact> art);

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