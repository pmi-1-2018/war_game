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