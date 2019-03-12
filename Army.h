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
		int thisArmy{ 0 };
		int otherArmy{ 0 };
		do
		{
			incomingDamage = listOfUnits[thisArmy].GetDamage() - a.listOfUnits[otherArmy].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(listOfUnits[thisArmy]) == typeid(archer))
				{
					incomingDamage += listOfUnits[thisArmy + 1].GetDamage() - a.listOfUnits[otherArmy].GetDefense();
				}
			}
			backDamage = a.listOfUnits[otherArmy].GetDamage() - listOfUnits[thisArmy].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(a.listOfUnits[numberOfUnits - 1]) == typeid(archer))
				{
					backDamage += a.listOfUnits[otherArmy + 1].GetDamage() - listOfUnits[thisArmy].GetDefense();
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
			if ((a.listOfUnits[otherArmy].GetHealthPoints() - incomingDamage) <= 0)
			{
				otherArmy ++;
			}
			else
			{
				a.listOfUnits[otherArmy].SetHealthPoints(a.listOfUnits[otherArmy].GetHealthPoints() - incomingDamage);
			}
			if ((listOfUnits[thisArmy].GetHealthPoints() - backDamage) <= 0)
			{
				thisArmy ++;
			}
			else
			{
				listOfUnits[thisArmy].SetHealthPoints(listOfUnits[thisArmy].GetHealthPoints() - backDamage);
			}
		} while ((thisArmy != numberOfUnits) || (otherArmy != a.numberOfUnits));
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