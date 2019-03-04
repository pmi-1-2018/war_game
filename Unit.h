#pragma once
#include<iostream>
#include<string>

using namespace std;

class Unit
{
protected:
	int healthPoints;
	int attack;
	int damage;
public:
	virtual void Attack(Unit unit, double distance) {};
	virtual void getDamage(int attack) {};
};

class Archer : public Unit
{
private:

public:
	bool ifArcher(Unit u)
	{
		if (u == Archer)
		{
			return true;
		}
		else
		{
			rerurn false;
		}
	}

};
class Swordsman : public Unit
{
private:
public:

};
class Lancer : public Unit
{
private:
	int protection;
public:


};