#include <iostream>
#include <string>
#include <typeinfo>
//#include "Unit.h"
//#include "Archer.h"
#include "Army.h"

Army::Army() :nameOfArmy("default") {}

Army::Army(string name, Unit*list, int num, char symb)
{
	nameOfArmy = name;
	for (int i = 0; i < numberOfUnits; i++)
	{
		units[i] = list[i];
	}
	this->symb = symb;
	switch (symb)
	{
		case 'F':
		{
			id = 1;
			break;
		}
		case 'S':
		{
			id = 2;
			break;
		}
	}
}

void Army::armyAttack(Army a) {
	int incomingDamage = 0;
	int backDamage = 0;
	Archer archer = Archer();
	int thisArmy{ 0 };
	int otherArmy{ 0 };
	do
	{
		incomingDamage = units[thisArmy].GetDamage() - a.units[otherArmy].GetDefense();
		if (numberOfUnits >= 2)
		{
			if (typeid(units[thisArmy]) == typeid(archer))
			{
				incomingDamage += units[thisArmy + 1].GetDamage() - a.units[otherArmy].GetDefense();
			}
		}
		backDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
		if (numberOfUnits >= 2)
		{
			if (typeid(a.units[numberOfUnits - 1]) == typeid(archer))
			{
				backDamage += a.units[otherArmy + 1].GetDamage() - units[thisArmy].GetDefense();
			}
		}
		if (incomingDamage < 0)
		{
			incomingDamage = 0;
		}
		if (backDamage < 0)
		{
			backDamage = 0;
		}
		if ((a.units[otherArmy].GetHealthPoints() - incomingDamage) <= 0)
		{
			otherArmy++;
		}
		else
		{
			a.units[otherArmy].SetHealthPoints(a.units[otherArmy].GetHealthPoints() - incomingDamage);
		}
		if ((units[thisArmy].GetHealthPoints() - backDamage) <= 0)
		{
			thisArmy++;
		}
		else
		{
			units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - backDamage);
		}
	} while ((thisArmy != numberOfUnits) || (otherArmy != a.numberOfUnits));
}

istream&operator>>(istream&is, Army &army) {
	is >> army.nameOfArmy;
	is >> army.numberOfUnits;
	for (int i = 0; i < army.numberOfUnits; i++)
	{
		//is >> army.units[i];
	}
	return is;
}
void Army::inputTheArmy(Army army) {
	cin >> army;
}

int Army::getNumber()
{
	return numberOfUnits;
}

Unit *Army::getWarriors()
{
	return units;
}

bool Army::isDead(Unit unit)
{
	if (unit.GetHealthPoints() == 0 && unit.GetHealthPoints() < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Army::armyMove(Unit*list, int number)
{
	if (isDead(list[0]))
	{
		Unit*newList = new Unit[number - 1];
		for (int i = 1; i < number; i)
		{
			newList[i - 1] = list[i];
		}
		delete[]list;
		for (int j = 0; j < number - 1; j)
		{
			list[j] = newList[j];
		}
		delete[]newList;
	}
}
char Army::GetSymb()
{
	return this->symb;
}
int Army::GetId()
{
	return this->id;
}
void Army::addUnit(Unit unit)
{
	Unit *temp = new Unit[numberOfUnits];
	for (int i = 0; i < numberOfUnits; i++)
	{
		temp[i] = units[i];
	}

	numberOfUnits++;
	units = new Unit[numberOfUnits];

	for (int i = 0; i < numberOfUnits - 1; i++)
	{
		units[i] = temp[i];
	}
	units[numberOfUnits - 1] = unit;
}