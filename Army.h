#include <iostream>
#include <string>
#include <typeinfo>
#include "Unit.h"
#include "Archer.h"

using namespace std;

class Army
{
private:
	string nameOfArmy;
	Unit *units;
	int numberOfUnits;
public:
	Army() :nameOfArmy("default") {};
	Army(string name, Unit*list, int num)
	{
		nameOfArmy = name;
		for (int i = 0; i < numberOfUnits; i++)
		{
			units[i] = list[i];
		}
	}

	void armyAttack(Army a)
	{
		int incomingDamage = 0;
		int backDamage = 0;
		Archer archer = Archer();
		do
		{
			incomingDamage = listOfUnits[numberOfUnits - 1].GetDamage() - a.listOfUnits[numberOfUnits - 1].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(listOfUnits[numberOfUnits - 1]) == typeid(archer))
				{
					incomingDamage += listOfUnits[numberOfUnits - 2].GetDamage() - a.listOfUnits[numberOfUnits - 1].GetDefense();
				}
			}
			backDamage = a.listOfUnits[a.numberOfUnits - 1].GetDamage() - a.listOfUnits[a.numberOfUnits - 1].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(a.listOfUnits[numberOfUnits - 1]) == typeid(archer))
				{
					backDamage += a.listOfUnits[a.numberOfUnits - 2].GetDamage() - a.listOfUnits[a.numberOfUnits - 1].GetDefense();
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
			if ((a.listOfUnits[numberOfUnits - 1].GetHealthPoints() - incomingDamage) <= 0)
			{
				a.numberOfUnits -= 1;
			}
			else
			{
				a.listOfUnits[numberOfUnits - 1].SetHealthPoints(a.listOfUnits[numberOfUnits - 1].GetHealthPoints() - incomingDamage);
			}
			if ((listOfUnits[numberOfUnits - 1].GetHealthPoints() - backDamage) <= 0)
			{
				numberOfUnits -= 1;
			}
			else
			{
				listOfUnits[numberOfUnits - 1].SetHealthPoints(listOfUnits[numberOfUnits - 1].GetHealthPoints() - backDamage);
			}
		} while ((numberOfUnits != 0) || (a.numberOfUnits != 0));
	}


	friend istream&operator>>(istream&is, Army &army)
	{
		is >> army.nameOfArmy;
		is >> army.numberOfUnits;
		for (int i = 0; i < army.numberOfUnits; i++)
		{
			is >> army.units[i];
		}
		return is;
	}
	void inputTheArmy(Army army)
	{
		cin >> army;
	}

	int getNumber()
	{
		return numberOfUnits;
	}

	Unit *getWarriors()
	{
		return units;
	}

	bool isDead(Unit unit)
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

	void armyMove(Unit*list, int number)
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

	//armyAttack

	void addUnit(Unit unit)
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

	//armyMove
};