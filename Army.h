#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class Army
{
private:
	string nameOfArmy;
	Warrior *warriors;
	int numberOfWarriors;
public:
	Army() :nameOfArmy("default") {};
	Army(string name, Warrior*list, int num)
	{
		nameOfArmy = name;
		for (int i = 0; i < numberOfWarriors; i++)
		{
			warriors[i] = list[i];
		}
	}

	void armyAttack(Army a)
	{
		int incomingDamage = 0;
		int backDamage = 0;
		Archer archer = Archer();
		do
		{
			incomingDamage = listOfUnits[numberOfWarriors - 1].getDamage() - a.listOfUnits[numberOfWarriors - 1].getArmor();
			if (numberOfWarriors >= 2)
			{
				if (typeid(listOfUnits[numberOfWarriors - 1]) == typeid(archer))
				{
					incomingDamage += listOfUnits[numberOfWarriors - 2].getDamage() - a.listOfUnits[numberOfWarriors - 1].getArmor();
				}
			}
			backDamage = a.listOfUnits[a.numberOfWarriors - 1].getDamage() - a.listOfUnits[a.numberOfWarriors - 1].getArmor();
			if (numberOfWarriors >= 2)
			{
				if (typeid(a.listOfUnits[numberOfWarriors - 1]) == typeid(archer))
				{
					backDamage += a.listOfUnits[a.numberOfWarriors - 2].getDamage() - a.listOfUnits[a.numberOfWarriors - 1].getArmor();
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
			if ((a.listOfUnits[numberOfWarriors - 1].getHealth() - incomingDamage) <= 0)
			{
				a.numberOfWarriors -= 1;
			}
			else
			{
				a.listOfUnits[numberOfWarriors - 1].setHealth(a.listOfUnits[numberOfWarriors - 1].getHealth() - incomingDamage);
			}
			if ((listOfUnits[numberOfWarriors - 1].getHealth() - backDamage) <= 0)
			{
				numberOfWarriors -= 1;
			}
			else
			{
				listOfUnits[numberOfWarriors - 1].setHealth(listOfUnits[numberOfWarriors - 1].getHealth() - backDamage);
			}
		} while ((numberOfWarriors != 0) || (a.numberOfWarriors != 0));
	}


	friend istream&operator>>(istream&is, Army &army)
	{
		is >> army.nameOfArmy;
		is >> army.numberOfWarriors;
		for (int i = 0; i < army.numberOfWarriors; i++)
		{
			is >> army.warriors[i];
		}
		return is;
	}
	void inputTheArmy(Army army)
	{
		cin >> army;
	}

	int getNumber()
	{
		return numberOfWarriors;
	}

	Warrior *getWarriors()
	{
		return warriors;
	}

	bool isDead(Warrior unit)
	{
		if (unit.getHp() == 0 && unit.getHp() < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void armyMove(Warrior*list, int number)
	{
		if (isDead(list[0]))
		{
			Warrior*newList = new Warrior[number - 1];
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

	void addUnit(Warrior unit)
	{
		Warrior *temp = new Warrior[numberOfWarriors];
		for (int i = 0; i < numberOfWarriors; i++)
		{
			temp[i] = warriors[i];
		}
			
		numberOfWarriors++;
		warriors = new Warrior[numberOfWarriors];

		for (int i = 0; i < numberOfWarriors - 1; i++)
		{
			warriors[i] = temp[i];
		}
		warriors[numberOfWarriors - 1] = unit;
	}

	//armyMove
};