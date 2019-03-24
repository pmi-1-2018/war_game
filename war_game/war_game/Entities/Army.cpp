#include <iostream>
#include <string>
#include <typeinfo>
#include "Archer.h"
#include "Army.h"
#include "Swordsman.h"

Army::Army() :nameOfArmy("default"), numberOfUnits(5), units(new Unit[5]) {}
/*
Army::Army(string name, Unit*list, int num, char symb) {

	nameOfArmy = name;
	numberOfUnits = num;
	this->symb = symb;

	for (int i = 0; i < numberOfUnits; i++)
	{
		units[i] = list[i];
	}
}
*/


Army::Army(string name, Unit*list, int num, char symb)
{
	nameOfArmy = name;
	//list = new Unit[num];
	//for (int i = 0; i < num; i++)
	//{
	//	units[i] = list[i];
	//}
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

//Army::Army(const Army &army)
//{
//	this->nameOfArmy = army.nameOfArmy;
//	this->symb = army.symb;
//	this->id = army.id;
//	this->numberOfUnits = army.numberOfUnits;
//	if (this->units != nullptr)
//	{
//		delete[] this->units;
//	}
//	for (int i = 0; i < this->numberOfUnits; i++)
//	{
//		this->units[i] = army.units[i];
//	}
//}

void Army::inputTheArmy() {
	char type;
	Swordsman s;
	Archer a;
	for (int i = 0; i < this->numberOfUnits; i++) {
		cout << "Enter the type of unit " << endl;
		cin >> type;
		switch (type) {
		case 'S':
			this->units[i] = s;
			break;
		case 'A':
			this->units[i] = a;
			break;
		default:
			break;
		}
	}
}


bool Army::armyAutoAttack(Army a)
{
	int outcomingDamage;
	int incomingDamage;
	int thisArmy{ 0 };
	int otherArmy{ 0 };
	system("CLS");
	this->printArmies(a, thisArmy, otherArmy);
	do
	{
		outcomingDamage = units[thisArmy].GetDamage() - a.units[otherArmy].GetDefense();
		if (numberOfUnits - thisArmy >= 2)
		{
			if (units[thisArmy + 1].getId() == 2)
			{
				outcomingDamage += units[thisArmy + 1].GetDamage() - a.units[otherArmy].GetDefense();
			}
		}
		if (outcomingDamage < 0)
		{
			outcomingDamage = 0;
		}
		if ((a.units[otherArmy].GetHealthPoints() - outcomingDamage) <= 0)
		{
			otherArmy++;

		}
		else
		{
			a.units[otherArmy].SetHealthPoints(a.units[otherArmy].GetHealthPoints() - outcomingDamage);
		}
		if (otherArmy != a.numberOfUnits)
		{
			incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
			if (a.numberOfUnits - otherArmy >= 2)
			{
				if (a.units[otherArmy + 1].getId() == 2)
				{
					incomingDamage += a.units[otherArmy + 1].GetDamage() - units[thisArmy].GetDefense();
				}
			}
			if (incomingDamage < 0)
			{
				incomingDamage = 0;
			}
			if ((units[thisArmy].GetHealthPoints() - incomingDamage) <= 0)
			{
				thisArmy++;
			}
			else
			{
				units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - incomingDamage);
			}
		}

		this->printArmiesFight(a, thisArmy, otherArmy, incomingDamage, outcomingDamage);
	} while ((thisArmy != numberOfUnits) && (otherArmy != a.numberOfUnits));
	if (thisArmy == numberOfUnits)
	{
		cout << "you lost";
		return false;
	}
	cout << "you won";
	return true;
}

bool Army::battlePVE(Army a)
{
	double outcomingDamage = 0;
	double incomingDamage = 0;
	int thisArmy = 0;
	int otherArmy = 0;
	Archer archer;
	int action = 2;
	int n = 0;
	do
	{
		cin >> action;
		if (action == 0)
		{
			outcomingDamage = units[thisArmy].GetDamage() - a.units[otherArmy].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(units[thisArmy + 1]) == typeid(archer))
				{
					outcomingDamage += units[thisArmy + 1].GetDamage() - a.units[otherArmy].GetDefense();
				}
			}
			if (outcomingDamage < 0)
			{
				outcomingDamage = 0;
			}
			if ((a.units[otherArmy].GetHealthPoints() - outcomingDamage) <= 0)
			{
				otherArmy++;

			}
			else
			{
				a.units[otherArmy].SetHealthPoints(a.units[otherArmy].GetHealthPoints() - outcomingDamage);
			}
			if (a.numberOfUnits - 1 != otherArmy)
			{
				incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
				if (numberOfUnits >= 2)
				{
					if (typeid(a.units[otherArmy + 1]) == typeid(archer))
					{
						incomingDamage += a.units[otherArmy + 1].GetDamage() - units[thisArmy].GetDefense();
					}
				}
				if (incomingDamage < 0)
				{
					incomingDamage = 0;
				}
				if ((units[thisArmy].GetHealthPoints() - incomingDamage) <= 0)
				{
					thisArmy++;
				}
				else
				{
					units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - incomingDamage);
				}
			}
		}
		if (action == 1)
		{
			cin >> n;
			swap(units[n], units[n + 1]);
			incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(a.units[otherArmy + 1]) == typeid(archer))
				{
					incomingDamage += a.units[otherArmy + 1].GetDamage() - units[thisArmy].GetDefense();
				}
			}
			if (incomingDamage < 0)
			{
				incomingDamage = 0;
			}
			if ((units[thisArmy].GetHealthPoints() - incomingDamage) <= 0)
			{
				thisArmy++;
			}
			else
			{
				units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - incomingDamage);
			}
		}
	} while (numberOfUnits - 1 != thisArmy || a.numberOfUnits - 1 != otherArmy);
	if (thisArmy != numberOfUnits)
	{
		return false;
	}
	return true;
}
bool Army::battlePVP(Army a)
{
	double outcomingDamage = 0;
	double incomingDamage = 0;
	int thisArmy = 0;
	int otherArmy = 0;
	Archer archer;
	int action;
	int n = 0;
	do
	{
		cin >> action;
		if (action == 0)
		{
			outcomingDamage = units[thisArmy].GetDamage() - a.units[otherArmy].GetDefense();
			if (numberOfUnits >= 2)
			{
				if (typeid(units[thisArmy + 1]) == typeid(archer))
				{
					outcomingDamage += units[thisArmy + 1].GetDamage() - a.units[otherArmy].GetDefense();
				}
			}
			if (outcomingDamage < 0)
			{
				outcomingDamage = 0;
			}
			if ((a.units[otherArmy].GetHealthPoints() - outcomingDamage) <= 0)
			{
				otherArmy++;

			}
			else
			{
				a.units[otherArmy].SetHealthPoints(a.units[otherArmy].GetHealthPoints() - outcomingDamage);
			}
			if (a.numberOfUnits != otherArmy)
			{
				incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
				if (numberOfUnits >= 2)
				{
					if (typeid(a.units[otherArmy + 1]) == typeid(archer))
					{
						incomingDamage += a.units[otherArmy + 1].GetDamage() - units[thisArmy].GetDefense();
					}
				}
				if (incomingDamage < 0)
				{
					incomingDamage = 0;
				}
				if ((units[thisArmy].GetHealthPoints() - incomingDamage) <= 0)
				{
					thisArmy++;
				}
				else
				{
					units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - incomingDamage);
				}
			}
		}
		else
		{
			cin >> n;
			swap(units[n], units[n + 1]);
		}
		cin >> action;
		if (action == 0)
		{
			incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
			if (a.numberOfUnits >= 2)
			{
				if (typeid(a.units[otherArmy + 1]) == typeid(archer))
				{
					incomingDamage += a.units[otherArmy + 1].GetDamage() - units[thisArmy].GetDefense();
				}
			}
			if (incomingDamage < 0)
			{
				incomingDamage = 0;
			}
			if ((units[thisArmy].GetHealthPoints() - incomingDamage) <= 0)
			{
				thisArmy++;
			}
			else
			{
				units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - incomingDamage);
			}
			if (numberOfUnits != thisArmy)
			{
				outcomingDamage = units[thisArmy].GetDamage() - a.units[otherArmy].GetDefense();
				if (a.numberOfUnits >= 2)
				{
					if (typeid(units[thisArmy + 1]) == typeid(archer))
					{
						outcomingDamage += units[thisArmy + 1].GetDamage() - a.units[otherArmy].GetDefense();
					}
				}
				if (outcomingDamage < 0)
				{
					outcomingDamage = 0;
				}
				if ((a.units[otherArmy].GetHealthPoints() - outcomingDamage) <= 0)
				{
					otherArmy++;
				}
				else
				{
					a.units[otherArmy].SetHealthPoints(a.units[otherArmy].GetHealthPoints() - outcomingDamage);
				}
			}
		}
		else
		{
			cin >> n;
			swap(a.units[n], a.units[n + 1]);
		}
	} while (numberOfUnits != thisArmy || a.numberOfUnits != otherArmy);
	if (thisArmy != numberOfUnits)
	{
		return false;
	}
	return true;
}
/*
istream&operator<<(ostream&os, Army &army) {
	os << army.nameOfArmy;
	os << army.numberOfUnits;
	for (int i = 0; i < army.numberOfUnits; i++)
	{
		is >> army.units[i];

	}
	return is;
}
*/

void Army::printArmy()
{
	for (int i = 0; i < this->numberOfUnits; i++)
	{
		cout << this->units[i];
	}
	cout << endl;
	system("pause");
}

void Army::printArmiesFight(Army a, int thisArmy, int otherArmy,int incomingDamage,int outcomingDamage)
{
	system("CLS");
	for (size_t i = 0; i < numberOfUnits-thisArmy; i++)
	{
		cout << " ";
	}
	cout << "-" << incomingDamage << "     " << "-" << outcomingDamage << endl;
	for (size_t i = 0; i < numberOfUnits - thisArmy; i++)
	{
		cout << units[numberOfUnits - i - 1];
	}
	cout << "     ";
	for (size_t i = 0; i < a.numberOfUnits - otherArmy; i++)
	{
		cout << a.units[i + otherArmy];
	}
	cout << endl;
	system("pause");
}

void Army::printArmies(Army a, int thisArmy, int otherArmy)
{
	for (size_t i = 0; i < numberOfUnits - thisArmy; i++)
	{
		cout << units[numberOfUnits - i - 1];
	}
	cout << "     ";
	for (size_t i = 0; i < a.numberOfUnits - otherArmy; i++)
	{
		cout << a.units[i + otherArmy];
	}
	cout << endl;
	system("pause");
}

int Army::getNumber()
{
	return numberOfUnits;
}

Unit Army::getWarriors()
{
	return *units;
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