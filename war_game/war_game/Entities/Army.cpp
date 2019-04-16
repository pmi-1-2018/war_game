#include <string>
#include <typeinfo>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include "Army.h"


Army::Army() :nameOfArmy("default"), numberOfUnits(5), units(new Unit[5]) {}
Army::Army(string name, Unit*list, int num, char symb, bool isPlayer)
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
		this->dec_energy += units[i].GetDecEnergy();
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
	this->isPlayer = isPlayer;
	this->isBotArmy = isPlayer == true ? false : true;

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

//
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


bool Army::armyAutoAttack(Army& a)
{
	using namespace std::this_thread;
	using namespace std::chrono;
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
		sleep_for(seconds(1));
	} while ((thisArmy != numberOfUnits) && (otherArmy != a.numberOfUnits));
	if (otherArmy == a.numberOfUnits)
	{
		delete[] a.units;
		CalcLevelAndCapacity(otherArmy);
		Unit* copy = new Unit[5];
		for (size_t i = 0; i < numberOfUnits - thisArmy; i++)
		{
			copy[i] = units[i + thisArmy];
		}
		delete[] units;
		units = copy;
		numberOfUnits -= thisArmy;
		dec_energy = 0;
		for (size_t i = 0; i < numberOfUnits; i++)
		{
			dec_energy += units[i].GetDecEnergy();
		}
		cout << "you won" << endl;
		return true;
	}
	if (thisArmy == numberOfUnits)
	{
		delete[] units;
		Unit* copy = new Unit[5];
		for (size_t i = 0; i < a.numberOfUnits - otherArmy; i++)
		{
			copy[i] = a.units[i + otherArmy];
		}
		delete[] a.units;
		a.units = copy;
		a.numberOfUnits -= otherArmy;
		cout << "you lost" << endl;
		return false;
	}
}
void Army::setIsPlayer(bool val)
{
	this->isPlayer = val;
}
bool Army::getIsPlayer()
{
	return isPlayer;
}
bool Army::getIsBotArmy()
{
	return isBotArmy;
}
void Army::setIsBotArmy(bool value)
{
	this->isBotArmy = value;
}
bool Army::battlePVE(Army& a)
{
	double outcomingDamage = 0;
	double incomingDamage = 0;
	int thisArmy = 0;
	int otherArmy = 0;
	char action;
	int index1 = 0;
	int index2 = 0;
	system("CLS");
	this->printArmies(a, thisArmy, otherArmy);
	do
	{
		cout << "press A to attack, press S to swap";
		action = _getch();
		if (action == 'A' || action == 'a')
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
			if (a.numberOfUnits != otherArmy)
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
			incomingDamage = 0;
			outcomingDamage = 0;
		}
		if (action == 'S')
		{
			this->swapUnits_1(index1, index2, a, numberOfUnits - thisArmy, a.numberOfUnits - otherArmy);
			swap(units[index1], units[index2]);

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
			system("CLS");
			this->printArmiesFight(a, thisArmy, otherArmy, incomingDamage, outcomingDamage);
		}
	} while (numberOfUnits != thisArmy && a.numberOfUnits != otherArmy);
	if (otherArmy == a.numberOfUnits)
	{
		delete[] a.units;
		Unit* copy = new Unit[5];
		CalcLevelAndCapacity(otherArmy);
		for (size_t i = 0; i < numberOfUnits - thisArmy; i++)
		{
			copy[i] = units[i + thisArmy];
		}
		delete[] units;
		units = copy;
		numberOfUnits -= thisArmy;
		dec_energy = 0;
		for (size_t i = 0; i < numberOfUnits; i++)
		{
			dec_energy += units[i].GetDecEnergy();
		}
		cout << "you won" << endl;
		return true;
	}
	if (thisArmy == numberOfUnits)
	{
		delete[] units;
		Unit* copy = new Unit[5];
		for (size_t i = 0; i < a.numberOfUnits - otherArmy; i++)
		{
			copy[i] = a.units[i + otherArmy];
		}
		delete[] a.units;
		a.units = copy;
		a.numberOfUnits -= otherArmy;
		cout << "you lost" << endl;
		return false;
	}
}
bool Army::battlePVP(Army& a)
{
	double outcomingDamage = 0;
	double incomingDamage = 0;
	int thisArmy = 0;
	int otherArmy = 0;
	char action;
	int index1 = 0;
	int index2 = 0;
	system("CLS");
	this->printArmies(a, thisArmy, otherArmy);
	do
	{
		cout << "press A to attack, press S to swap";
		action = _getch();
		if (action == 'A' || action == 'a')
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
			if (a.numberOfUnits != otherArmy)
			{
				incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
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
			system("CLS");
			this->printArmiesFight(a, thisArmy, otherArmy, incomingDamage, outcomingDamage);

		}
		else
		{
			this->swapUnits_1(index1, index2, a, numberOfUnits - thisArmy, a.numberOfUnits - otherArmy);
			swap(units[index1], units[index2]);
			system("CLS");
			this->printArmies(a, thisArmy, otherArmy);
		}
		if (numberOfUnits != thisArmy && a.numberOfUnits != otherArmy)
		{
			cout << "\npress A to attack, press S to swap";
			action = _getch();
			if (action == 'A' || action == 'a')
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
				if (numberOfUnits != thisArmy)
				{
					outcomingDamage = units[thisArmy].GetDamage() - a.units[otherArmy].GetDefense();
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
					system("CLS");
					this->printArmiesFight(a, thisArmy, otherArmy, incomingDamage, outcomingDamage);
				}
			}
			else
			{
				a.swapUnits_2(index1, index2, *this, numberOfUnits - thisArmy, a.numberOfUnits - otherArmy);
				swap(a.units[index1], a.units[index2]);
				system("CLS");
				this->printArmies(a, thisArmy, otherArmy);
			}
		}
	} while (numberOfUnits != thisArmy && a.numberOfUnits != otherArmy);
	if (otherArmy == a.numberOfUnits)
	{
		delete[] a.units;
		Unit* copy = new Unit[5];
		CalcLevelAndCapacity(otherArmy);
		for (size_t i = 0; i < numberOfUnits - thisArmy; i++)
		{
			copy[i] = units[i + thisArmy];
		}
		delete[] units;
		units = copy;
		numberOfUnits -= thisArmy;
		dec_energy = 0;
		for (size_t i = 0; i < numberOfUnits; i++)
		{
			dec_energy += units[i].GetDecEnergy();
		}
		cout << endl << symb << "  won" << endl;
		this->printArmy();
		return true;
	}
	if (thisArmy == numberOfUnits)
	{
		delete[] units;
		Unit* copy = new Unit[5];
		CalcLevelAndCapacity(thisArmy);
		for (size_t i = 0; i < a.numberOfUnits - otherArmy; i++)
		{
			copy[i] = a.units[i + otherArmy];
		}
		delete[] a.units;
		a.units = copy;
		a.numberOfUnits -= otherArmy;
		a.dec_energy = 0;
		for (size_t i = 0; i < a.numberOfUnits; i++)
		{
			a.dec_energy += a.units[i].GetDecEnergy();
		}
		cout << endl << a.symb << "  won" << endl;
		a.printArmy();
		return false;
	}
}

void Army::printArmy()
{
	for (int i = 0; i < this->numberOfUnits; i++)
	{
		cout << this->units[i];
	}
	cout << endl;
	system("pause");
}

void Army::printArmiesFight(Army& a, int thisArmy, int otherArmy, int incomingDamage, int outcomingDamage)
{
	system("CLS");
	for (size_t i = 2; i < numberOfUnits - thisArmy; i++)
	{
		cout << " ";
	}
	cout << "-" << incomingDamage << "  " << "-" << outcomingDamage << endl;
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
}

void Army::printArmies(Army& a, int thisArmy, int otherArmy)
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
}

Army & Army::operator=(const Army & army)
{
	this->nameOfArmy = army.nameOfArmy;
	this->numberOfUnits = army.numberOfUnits;
	this->symb = army.symb;
	this->id = army.id;
	this->dec_energy = army.dec_energy;
	this->currentEnergy = army.currentEnergy;
	this->isPlayer = army.isPlayer;
	this->isBotArmy = army.isBotArmy;
	this->units = new Unit[this->numberOfUnits];
	for (int i = 0; i < this->numberOfUnits; i++)
	{
		this->units[i] = army.units[i];
	}
	return *this;
}

int Army::getNumber()
{
	return numberOfUnits;
}

Unit* Army::getWarriors()
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
int Army::getNumberOfUnits()
{
	return numberOfUnits;
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


void printSpace(int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << ' ';
	}
}



void Army::swapUnits_1(int & index1, int & index2, Army& army2, int alive_count_army1, int alive_count_army2)
{
	if (alive_count_army1 < 2)
	{
		cout << "You have no enough units to swap\n";
		index1 = -1;
		index2 = -1;
		return;
	}
	system("cls");
	index1 = 0;
	index2 = 0;

	for (int i = numberOfUnits - 1; i >= numberOfUnits - alive_count_army1; i--)
	{
		cout << units[i];
	}
	printSpace(4);
	for (int i = army2.numberOfUnits - alive_count_army2; i < army2.numberOfUnits; i++)
	{
		cout << army2.getWarriors()[i];
	}
	cout << endl;
	printSpace(alive_count_army1 - 1);
	cout << '^';
	cout << "\nFirst unit index: " << index1;
	cout << "\nSecond unit index: ";
	cout << "\nPress Enter to select the first unit to swap.";

	bool isSelected = false;
	do
	{
		isSelected = false;
		switch (_getch())
		{
		case 13:
		{
			isSelected = true;
			break;
		}
		case 75:
		{
			if (index1 != alive_count_army1 - 1)
			{
				index1++;
				system("cls");
				for (int i = numberOfUnits - 1; i >= numberOfUnits - alive_count_army1; i--)
				{
					cout << units[i];
				}
				printSpace(4);
				for (int i = army2.numberOfUnits - alive_count_army2; i < army2.numberOfUnits; i++)
				{
					cout << army2.getWarriors()[i];
				}
				cout << endl;
				printSpace(alive_count_army1 - 1 - index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}


			break;
		}
		case 77:
		{
			if (index1 != 0)
			{
				index1--;
				system("cls");
				for (int i = numberOfUnits - 1; i >= numberOfUnits - alive_count_army1; i--)
				{
					cout << units[i];
				}
				printSpace(4);
				for (int i = army2.numberOfUnits - alive_count_army2; i < army2.numberOfUnits; i++)
				{
					cout << army2.getWarriors()[i];
				}
				cout << endl;
				printSpace(alive_count_army1 - 1 - index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}
			break;
		}
		}

	} while (isSelected == false);



	system("cls");
	for (int i = numberOfUnits - 1; i >= numberOfUnits - alive_count_army1; i--)
	{
		if (i == index1 + numberOfUnits - alive_count_army1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
			cout << units[i];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			cout << units[i];
		}

	}
	printSpace(4);
	for (int i = army2.numberOfUnits - alive_count_army2; i < army2.numberOfUnits; i++)
	{
		cout << army2.getWarriors()[i];
	}
	cout << endl;
	printSpace(alive_count_army1 - 1);
	cout << '^';
	cout << "\nFirst unit index: " << index1;
	cout << "\nSecond unit index: " << index2;
	cout << "\nPress Enter to select the second unit to swap(the green one is selected).";

	do
	{
		isSelected = false;
		switch (_getch())
		{
		case 13:
		{
			if (index2 == index1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
				cout << "\nYou can`t select two equal indexes.";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				break;
			}
			isSelected = true;
			break;
		}
		case 75:
		{
			if (index2 != alive_count_army1 - 1)
			{
				index2++;
				system("cls");
				for (int i = numberOfUnits - 1; i >= numberOfUnits - alive_count_army1; i--)
				{
					if (i == index1 + numberOfUnits - alive_count_army1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}

				}
				printSpace(4);
				for (int i = army2.numberOfUnits - alive_count_army2; i < army2.numberOfUnits; i++)
				{
					cout << army2.getWarriors()[i];
				}
				cout << endl;
				printSpace(alive_count_army1 - 1 - index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}


			break;
		}
		case 77:
		{
			if (index2 != 0)
			{
				index2--;
				system("cls");
				for (int i = numberOfUnits - 1; i >= numberOfUnits - alive_count_army1; i--)
				{
					if (i == index1 + numberOfUnits - alive_count_army1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}

				}
				printSpace(4);
				for (int i = army2.numberOfUnits - alive_count_army2; i < army2.numberOfUnits; i++)
				{
					cout << army2.getWarriors()[i];
				}
				cout << endl;
				printSpace(alive_count_army1 - 1 - index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}
			break;
		}
		}
	} while (isSelected == false);
	index1 += numberOfUnits - alive_count_army1;
	index2 += numberOfUnits - alive_count_army1;
}


void Army::swapUnits_2(int & index1, int & index2, Army& army1, int alive_count_army1, int alive_count_army2)
{
	if (alive_count_army2 < 2)
	{
		cout << "You have no enough units to swap\n";
		index1 = -1;
		index2 = -1;
		return;
	}
	system("cls");
	index1 = 0;
	index2 = 0;

	for (int i = army1.numberOfUnits - 1; i >= army1.numberOfUnits - alive_count_army1; i--)
	{
		cout << army1.getWarriors()[i];
	}
	printSpace(4);
	for (int i = numberOfUnits - alive_count_army2; i < numberOfUnits; i++)
	{
		cout << units[i];
	}
	cout << endl;
	printSpace(alive_count_army1 + 4);
	cout << '^';
	cout << "\nFirst unit index: " << index1;
	cout << "\nSecond unit index: ";
	cout << "\nPress Enter to select the first unit to swap.";


	bool isSelected = false;
	do
	{
		isSelected = false;
		switch (_getch())
		{
		case 13:
		{
			isSelected = true;
			break;
		}
		case 75:
		{
			if (index1 != 0)
			{
				index1--;
				system("cls");
				for (int i = army1.numberOfUnits - 1; i >= army1.numberOfUnits - alive_count_army1; i--)
				{
					cout << army1.getWarriors()[i];
				}
				printSpace(4);
				for (int i = numberOfUnits - alive_count_army2; i < numberOfUnits; i++)
				{
					cout << units[i];
				}
				cout << endl;
				printSpace(alive_count_army1 + 4 + index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}


			break;
		}
		case 77:
		{
			if (index1 != alive_count_army2 - 1)
			{
				index1++;
				system("cls");
				for (int i = army1.numberOfUnits - 1; i >= army1.numberOfUnits - alive_count_army1; i--)
				{
					cout << army1.getWarriors()[i];
				}
				printSpace(4);
				for (int i = numberOfUnits - alive_count_army2; i < numberOfUnits; i++)
				{
					cout << units[i];
				}
				cout << endl;
				printSpace(alive_count_army1 + 4 + index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}
			break;
		}
		}

	} while (isSelected == false);



	system("cls");
	for (int i = army1.numberOfUnits - 1; i >= army1.numberOfUnits - alive_count_army1; i--)
	{
		cout << army1.getWarriors()[i];
	}
	printSpace(4);
	for (int i = numberOfUnits - alive_count_army2, k = 0; i < numberOfUnits; i++, k++)
	{
		if (k == index1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
			cout << units[i];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			cout << units[i];
		}
	}
	cout << endl;
	printSpace(alive_count_army1 + 4);
	cout << '^';
	cout << "\nFirst unit index: " << index1;
	cout << "\nSecond unit index: " << index2;
	cout << "\nPress Enter to select the second unit to swap(the green one is selected).";

	do
	{
		isSelected = false;
		switch (_getch())
		{
		case 13:
		{
			if (index2 == index1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
				cout << "\nYou can`t select two equal indexes.";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				break;
			}
			isSelected = true;
			break;
		}
		case 75:
		{
			if (index2 != 0)
			{
				index2--;
				system("cls");
				for (int i = army1.numberOfUnits - 1; i >= army1.numberOfUnits - alive_count_army1; i--)
				{
					cout << army1.getWarriors()[i];
				}
				printSpace(4);
				for (int i = numberOfUnits - alive_count_army2, k = 0; i < numberOfUnits; i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}
				}
				cout << endl;
				printSpace(alive_count_army1 + 4 + index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}	


			break;
		}
		case 77:
		{
			if (index2 != alive_count_army2 - 1)
			{
				index2++;
				system("cls");
				for (int i = army1.numberOfUnits - 1; i >= army1.numberOfUnits - alive_count_army1; i--)
				{
					cout << army1.getWarriors()[i];
				}
				printSpace(4);
				for (int i = numberOfUnits - alive_count_army2, k = 0; i < numberOfUnits; i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}
				}
				cout << endl;
				printSpace(alive_count_army1 + 4 + index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}
			break;
		}
		}
	} while (isSelected == false);
	index1 += numberOfUnits - alive_count_army2;
	index2 += numberOfUnits - alive_count_army2;

}
void Army::swapUnits()
{
	if (numberOfUnits < 2)
	{
		cout << "You have no enough units to swap\n";
		return;
	}
	system("cls");
	int index1 = 0;
	int index2 = 0;

	for (int i = 0; i < numberOfUnits; i++)
	{
		cout << units[i];
	}
	cout << endl;
	cout << '^';
	cout << "\nFirst unit index: " << index1;
	cout << "\nSecond unit index: ";
	cout << "\nPress Enter to select the first unit to swap.";


	bool isSelected = false;
	do
	{
		isSelected = false;
		switch (_getch())
		{
		case 13:
		{
			isSelected = true;
			break;
		}
		case 75:
		{
			if (index1 != 0)
			{
				index1--;
				system("cls");
				for (int i = 0; i < numberOfUnits; i++)
				{
					cout << units[i];
				}
				cout << endl;
				printSpace(index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}


			break;
		}
		case 77:
		{
			if (index1 != numberOfUnits - 1)
			{
				index1++;
				system("cls");
				for (int i = 0; i < numberOfUnits; i++)
				{
					cout << units[i];
				}
				cout << endl;
				printSpace(index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}
			break;
		}
		}

	} while (isSelected == false);



	system("cls");
	for (int i = 0, k = 0; i < numberOfUnits; i++, k++)
	{
		if (k == index1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
			cout << units[i];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			cout << units[i];
		}
	}
	cout << endl;
	cout << '^';
	cout << "\nFirst unit index: " << index1;
	cout << "\nSecond unit index: " << index2;
	cout << "\nPress Enter to select the second unit to swap(the green one is selected).";

	do
	{
		isSelected = false;
		switch (_getch())
		{
		case 13:
		{
			if (index2 == index1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
				cout << "\nYou can`t select two equal indexes.";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				break;
			}
			isSelected = true;
			break;
		}
		case 75:
		{
			if (index2 != 0)
			{
				index2--;
				system("cls");
				for (int i = 0, k = 0; i < numberOfUnits; i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}
				}
				cout << endl;
				printSpace(index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}


			break;
		}
		case 77:
		{
			if (index2 != numberOfUnits - 1)
			{
				index2++;
				system("cls");
				for (int i = 0, k = 0; i < numberOfUnits; i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}
				}
				cout << endl;
				printSpace(index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}
			break;
		}
		}
	} while (isSelected == false);
	swap(units[index1], units[2]);

}
int Army::GetLevel()
{
	return level;
}
int Army::GetExp() {
	return experience;
}
void Army::SetLevel(int a)
{
	level += a;
}

void Army::CalcLevelAndCapacity(int countOfDead)
{
	while (countOfDead)
	{
		experience++;
		if (experience == 3)
		{
			SetLevel(1);
			SetCapacity(1);
			experience = 0;
		}
		countOfDead--;
	}
}
void Army::SetCapacity(int a)
{
	capacity += a;
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
int Army::GetCapacity()
{
	return capacity;
}
