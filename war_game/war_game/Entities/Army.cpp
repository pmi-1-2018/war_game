#include <iostream>
#include <string>
#include <typeinfo>
#include "Archer.h"
#include "Army.h"

Army::Army()
{
	nameOfArmy = "default";
	this->numberOfUnits = 0;
	this->units = new Unit[0];
	this->symb = NULL;
	this->id = 0;
	this->capacity = 3;
	this->level = 0;
	this->experience = 0;
}

Army::Army(string name, Unit*list, int num, char symb)
{
	nameOfArmy = name;
	this->numberOfUnits = num;
	this->units = new Unit[num];
	this->dec_energy = 0;
	this->capacity = 3;
	this->level = 0;
	this->experience = 0;
	for (int i = 0; i < this->numberOfUnits; i++)
	{
		units[i] = list[i];
		this->dec_energy += units->GetDecEnergy();
	}
	this->currentEnergy = this->START_ENERGY + this->dec_energy;
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

Army::Army(const Army & army)
{
	this->nameOfArmy = army.nameOfArmy;
	this->symb = army.symb;
	this->id = army.id;
	this->numberOfUnits = army.numberOfUnits;
	this->level = army.level;
	this->capacity = army.capacity;
	this->experience = army.experience;
	if (this->units != nullptr) 
	{
		delete[] this->units;
	}
	for (int i=0; i<this->numberOfUnits; i++) 
	{
		this->units[i] = army.units[i];
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
	if (CheckCapacity()) {
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
}

bool Army::SetCurrEnergy(const int & value)
{
	this->currentEnergy += value;
	if (this->currentEnergy >= 0)
	{
		return false;
	}
	else 
	{
		this->currentEnergy = this->START_ENERGY + this->dec_energy;
		return true;
	}
}

int Army::GetCurrEnergy()
{
	return this->currentEnergy;
}

Army::~Army()
{
	if (this->units != nullptr) 
	{
		delete[] units;
	}
}
int Army::GetLevel()
{
	return level;
}
int Army::GetExp() {
	return experience;
}
void Army::SetLevel(Army army)
{
	int countOfDead = army.getNumber();
	while (countOfDead)
	{
		experience++;
		if (experience == 3)
		{
			level += 1;
			capacity += 1;
		}
		experience = 0;
		countOfDead--;
	}
}
bool Army::CheckCapacity()
{
	if (numberOfUnits < capacity)
	{
		cout << "You can add " << capacity - numberOfUnits << " units" << endl;
		return true;
	}
	if (numberOfUnits == capacity)
	{
		cout << "You cann't add units" << endl;
		return false;
	}
}

