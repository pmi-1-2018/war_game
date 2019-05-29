#include <string>
#include <typeinfo>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include "Army.h"

using namespace std::this_thread;
using namespace std::chrono;


Army::Army() :nameOfArmy("default"),  wallet(0) {}
Army::Army(string name, vector<Unit> list, char symb, bool isPlayer, int wallet)
{
	nameOfArmy = name;
	this->dec_energy = 0;
	this->capacity = 3;
	this->level = 0;
	this->experience = 0;
	for (int i = 0; i < list.size(); i++)
	{
		units.push_back(list[i]);
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
	this->inventory = new Inventory(3, 3, this);
	this->wallet = wallet;
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

void Army::increaseIncome(int value)
{
	this->income += value;
}

void Army::addMoneyToWallet(int value)
{
	this->wallet += value;
}

size_t Army::getStashPossibleSize()
{
	return this->stashSize;
}

int Army::getIncome()
{
	return this->income;
}

int Army::getWallet()
{
	return this->wallet;
}

int Army::GetCurrEnergy()
{
	return this->currentEnergy;
}

void Army::InventoryMode()
{
	system("cls");
	int selectedX, selectedY;
	selectedX = selectedY = 0;
	this->inventory->PrintInventory(selectedX, selectedY, false);
	while (true)
	{
		char key = _getch();
		int asciiValue = key;
		bool selectPressed = false;
		bool deletePressed = false;
		if (asciiValue == 105 || asciiValue == 27)
		{
			break;
		}
		if (asciiValue == 97) // pressed a
		{
			if (selectedX != 0)
			{
				selectedX -= 1;
			}
		}
		else if (asciiValue == 100) // pressed d
		{
			if (selectedX != this->inventory->inventoryWidth - 1)
			{
				selectedX += 1;
			}
		}
		else if (asciiValue == 119) // pressed w
		{
			if (selectedY != 0)
			{
				selectedY -= 1;
			}
		}
		else if (asciiValue == 115) // pressed s
		{
			if (selectedY != this->inventory->inventoryHeight - 1)
			{
				selectedY += 1;
			}
		}
		else if (asciiValue == 13)
		{
			selectPressed = true;
		}
		else if (asciiValue == 8) // pressed backspace
		{
			deletePressed = true;
		}
		system("cls");
		this->inventory->PrintInventory(selectedX, selectedY, selectPressed, deletePressed);
	}
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

void Army::inputTheArmy(size_t size) {
	char type;
	Swordsman s;
	Archer a;
	Wizard w;
	Tank t;
	Buffer b;
	Healer h;
	for (size_t i = 0; i < size;i++) {//this->units.size(); i++) {
		cout << "Enter the type of unit " << endl;
		cin >> type;
		switch (type) {
		case 'S':
			units.push_back(s);
			break;
		case 'A':
			units.push_back(a);
			break;
		case 'W':
			units.push_back(w);
			break;
		case 'T':
			units.push_back(t);
			break;
		case 'B':
			units.push_back(b);
			break;
		case 'H':
			units.push_back(h);
			break;
		default:
			cout << "Enter valid value! " << endl;
			break;
		}
	}
}

void Army::changeStartEnergy(int value)
{
	this->START_ENERGY += value;
}

void Army::changeArmyUnitsDefence(int value)
{
	int numberOfUnits = this->units.size();
	for (size_t i = 0; i < numberOfUnits; i++)
	{
		Unit* unit = &this->units[i];
		this->units[i].SetDamage(unit->GetDefense() + value);
	}
}

void Army::changeArmyUnitsAttack(int value)
{
	int numberOfUnits = this->units.size();
	for (size_t i = 0; i < numberOfUnits; i++)
	{
		Unit* unit = &this->units[i];
		this->units[i].SetDamage(unit->GetDamage() + value);
	}
}


bool Army::hit(Unit& u1, Unit& u2, vector<Artifact> thisArt, vector<Artifact> otherArt)
{
	u2.SetHealthPoints(u2.GetHealthPoints() - (u1.calculateDamage(thisArt) - u2.calculateDefence(otherArt)));
	return u2.GetHealthPoints() <= 0;
}


bool Army::armyAutoAttack(Army& a)
{
	int thisArmy = units.size();
	int otherArmy = a.units.size();
	bool check = true;
	system("CLS");
	int var = 0;
	this->printArmiesFight(a, true);
	do
	{
		this->buff();
		a.buff();
		this->heal();
		a.heal();
		this->fight(a,check);
		check = !check;
		sleep_for(seconds(1));
		if (units.size() != 0 && a.units.size() != 0)
		{
			a.fight(*this, check);
			check = !check;
			sleep_for(seconds(1));
		}
	} while ((units.size() != 0) && (a.units.size() != 0));
	if (a.units.size() == 0)
	{
		this->CalcLevelAndCapacity(otherArmy);
		dec_energy = 0;
		for (size_t i = 0; i < units.size(); i++)
		{
			dec_energy += units[i].GetDecEnergy();
		}
		return true;
	}
	return false;
	
}

bool Army::battlePVE(Army& a)
{
	int thisArmy = units.size();
	int otherArmy = a.units.size();
	char action;
	bool check = true;
	int index1 = 0;
	int index2 = 0;
	system("CLS");
	int var = 0;
	this->printArmiesFight(a,true);
	do
	{
		solve:
		cout << "press A to attack, press S to swap";
		action = _getch();
		if (action == 'A' || action == 'a')
		{
			this->buff();
			a.buff();
			this->heal();
			a.heal();
			this->fight(a,check);
			check = !check;
			sleep_for(seconds(1));
			if (units.size() != 0 && a.units.size() != 0)
			{
				a.fight(*this, check);
				check = !check;
				sleep_for(seconds(1));
			}
		}
		if (action == 'S' || action == 's')
		{
			this->swapUnits_1(index1, index2, a);
			if (index1 == -1)
				goto solve;
			swap(units[index1], units[index2]);
			this->buff();
			a.buff();
			this->heal();
			a.heal();
			a.fight(*this, false);
		}
	} while (units.size() != 0 && a.units.size() != 0);
	if (a.units.size() == 0)
	{
		this->CalcLevelAndCapacity(otherArmy);
		dec_energy = 0;
		for (size_t i = 0; i < units.size(); i++)
		{
			dec_energy += units[i].GetDecEnergy();
		}
		return true;
	}
	return false;
	
}

bool Army::battlePVP(Army& a)
{
	bool turn = true;
	int thisArmy = units.size();
	int otherArmy = a.units.size();
	char action;
	int index1 = 0;
	int index2 = 0;
	int var = 0;
	system("CLS");
	this->printArmiesFight(a, true);
	do
	{
		cout << endl;
		if (turn)
		{
			cout << "Attacker turn\n";
		}
		else
		{
			cout << "Defender turn\n";
		}
		/************************/
		DontKillMe:
		/***********************/
		cout << "press A to attack, press S to swap";
		action = _getch();
		if (action == 'A' || action == 'a')
		{
			if (turn == true)
			{
				this->buff();
				this->heal();
				this->fight(a, turn);
			}
			else
			{
				a.buff();
				a.heal();
				a.fight(*this, turn);
			}
			sleep_for(seconds(1));
		}
		if (action == 'S' || action == 's')
		{
			if (turn == true)
			{
				this->swapUnits_1(index1, index2, a);
				if (index1 == -1)
					goto DontKillMe;
				swap(units[index1], units[index2]);
				this->buff();
				this->heal();
			}
			else
			{
				a.swapUnits_2(index1, index2, *this);
				if (index1 == -1)
					goto DontKillMe;
				swap(a.units[index1], a.units[index2]);
				a.buff();
				a.heal();
			}
		}
		turn = !turn;
	} while (units.size() != 0 && a.units.size() != 0);
	if (a.units.size() == 0)
	{
		this->CalcLevelAndCapacity(otherArmy);
		dec_energy = 0;
		for (size_t i = 0; i < units.size(); i++)
		{
			dec_energy += units[i].GetDecEnergy();
		}
		return true;
	}
	if (units.size() == 0)
	{
		a.CalcLevelAndCapacity(thisArmy);
		a.dec_energy = 0;
		for (size_t i = 0; i < a.units.size(); i++)
		{
			a.dec_energy += a.units[i].GetDecEnergy();
		}
		return false;
	}
}

void Army::fight(Army& a, bool check)
{
	int i = 0;
	it = units.begin();
	a.it = a.units.begin();
	if (units[0].getId() != 4)
	{
		if (hit(units[0], a.units[0], inventory->getActiveArtifacts(), a.inventory->getActiveArtifacts()))
		{
			a.units.erase(a.it);
		}
		else
		{
			hit(a.units[0], units[0], a.inventory->getActiveArtifacts(), inventory->getActiveArtifacts());
		}
	}
	else
	{
		int index = 0;
		for (size_t i = 0; i < a.units.size(); i++, index++)
		{
			a.units[index].SetHealthPoints(a.units[index].GetHealthPoints() - units[0].calculateDamage(inventory->getActiveArtifacts())* 1.0 / (pow(2, i)));
			if (a.units[index].GetHealthPoints() <= 0)
			{
				it += index;
				a.units.erase(a.it);
				index--;
			}
			if (i == 2)
			{
				break;
			}
		}
	}
	printArmiesFight(a, check);
}

void Army::heal()
{
	Healer h;
	for (size_t i = 0; i < units.size(); i++)
	{
		if (units.size() >= 2)
		{
			if (units[i].getId() == 6)
			{
				if (i == 0)
				{
					h.Heal(units[i + 1]);
				}
				if (i == units.size() - 1)
				{
					h.Heal(units[i - 1]);
				}
				if (i != 0 && i != units.size() - 1)
				{
					h.Heal(units[i + 1]);
					h.Heal(units[i - 1]);
				}
			}
		}
	}
}

void Army::buff()
{
	int counter = 0;
	Buffer b;
	for (size_t i = 0; i < units.size(); i++)
	{
		if (units[i].getId() == 5)
		{
			counter++;
		}
	}
	system("cls");
	for (size_t i = 0; i < counter; i++)
	{
		b.BuffDamage(units[0]);
		b.BuffDefense(units[0]);
	}
}

void Army::printArmy()
{
	for (int i = 0; i < units.size(); i++)
	{
		cout << this->units[i];
	}
	cout << endl;
	system("pause");
}

void Army::printArmiesFight(Army& a, bool shit)
{
	system("CLS");
	if (shit)
	{
		for (size_t i = 0; i < units.size(); i++)
		{
			cout << units[units.size() - i - 1].GetHealthPoints() << " ";
		}
		cout << "  ";
		for (size_t i = 0; i < a.units.size(); i++)
		{
			cout << a.units[i].GetHealthPoints() << " ";
		}
		cout << endl;
		for (size_t i = 0; i < units.size(); i++)
		{
			cout << units[units.size() - i - 1] << " ";
		}
		cout << "     ";
		for (size_t i = 0; i < a.units.size(); i++)
		{
			cout << a.units[i] << " ";
		}
	}
	else
	{
		for (size_t i = 0; i < a.units.size(); i++)
		{
			cout << a.units[a.units.size() - i - 1].GetHealthPoints() << " ";
		}
		cout << "  ";
		for (size_t i = 0; i < units.size(); i++)
		{
			cout << units[i].GetHealthPoints() << " ";
		}
		cout << endl;
		for (size_t i = 0; i < a.units.size(); i++)
		{
			cout << a.units[a.units.size() - i - 1] << " ";
		}
		cout << "     ";
		for (size_t i = 0; i < units.size(); i++)
		{
			cout << units[i] << " ";
		}
	}
}

Army & Army::operator=(const Army & army)
{
	this->nameOfArmy = army.nameOfArmy;
	this->symb = army.symb;
	this->id = army.id;
	this->dec_energy = army.dec_energy;
	this->currentEnergy = army.currentEnergy;
	this->isPlayer = army.isPlayer;
	this->isBotArmy = army.isBotArmy;
	for (int i = 0; i < army.units.size(); i++)
	{
		this->units[i] = army.units[i];
	}
	return *this;
}


vector<Unit> Army::getUnits()
{
	return units;
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
	units.push_back(unit);
}

void printSpace(int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << ' ';
	}
}

void Army::swapUnits_1(int & index1, int & index2, Army& army2)
{
	if (units.size() < 2)
	{
		cout << "You have no enough units to swap\n";
		index1 = -1;
		index2 = -1;
		return;
	}
	system("cls");
	index1 = 0;
	index2 = 0;

	for (int i = units.size() - 1; i >= 0; i--)
	{
		cout << units[i];
	}
	printSpace(4);
	for (int i = 0; i < army2.units.size(); i++)
	{
		cout << army2.getUnits()[i];
	}
	cout << endl;
	printSpace(units.size() - 1);
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
			if (index1 != units.size() - 1)
			{
				index1++;
				system("cls");
				for (int i = units.size() - 1; i >= 0; i--)
				{
					cout << units[i];
				}
				printSpace(4);
				for (int i = 0; i < army2.units.size(); i++)
				{
					cout << army2.getUnits()[i];
				}
				cout << endl;
				printSpace(units.size() - 1 - index1);
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
				for (int i = units.size() - 1; i >= 0; i--)
				{
					cout << units[i];
				}
				printSpace(4);
				for (int i = 0; i < army2.units.size(); i++)
				{
					cout << army2.getUnits()[i];
				}
				cout << endl;
				printSpace(units.size() - 1 - index1);
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
	for (int i = units.size() - 1; i >= 0; i--)
	{
		if (i == index1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
			cout << units[i].getSymb();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			cout << units[i];
		}

	}
	printSpace(4);
	for (int i = 0; i < army2.units.size(); i++)
	{
		cout << army2.getUnits()[i];
	}
	cout << endl;
	printSpace(units.size() - 1);
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
			if (index2 != units.size() - 1)
			{
				index2++;
				system("cls");
				for (int i = units.size() - 1; i >= 0; i--)
				{
					if (i == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i].getSymb();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}

				}
				printSpace(4);
				for (int i = 0; i < army2.units.size(); i++)
				{
					cout << army2.getUnits()[i];
				}
				cout << endl;
				printSpace(units.size() - 1 - index2);
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
				for (int i = units.size() - 1; i >= 0; i--)
				{
					if (i == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i].getSymb();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}

				}
				printSpace(4);
				for (int i = 0; i < army2.units.size(); i++)
				{
					cout << army2.getUnits()[i];
				}
				cout << endl;
				printSpace(units.size() - 1 - index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}
			break;
		}
		}
	} while (isSelected == false);
}
void Army::swapUnits_2(int & index1, int & index2, Army& army1)
{
	if (units.size() < 2)
	{
		cout << "You have no enough units to swap\n";
		index1 = -1;
		index2 = -1;
		return;
	}
	system("cls");
	index1 = 0;
	index2 = 0;

	for (int i = army1.units.size() - 1; i >= 0; i--)
	{
		cout << army1.units[i];
	}
	printSpace(4);
	for (int i = 0; i < units.size(); i++)
	{
		cout << units[i];
	}
	cout << endl;
	printSpace(army1.units.size() + 4);
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
				for (int i = army1.units.size() - 1; i >= 0; i--)
				{
					cout << army1.units[i];
				}
				printSpace(4);
				for (int i = 0; i < units.size(); i++)
				{
					cout << units[i];
				}
				cout << endl;
				printSpace(army1.units.size() + 4 + index1);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: ";
				cout << "\nPress Enter to select the first unit to swap.";
			}


			break;
		}
		case 77:
		{
			if (index1 != units.size() - 1)
			{
				index1++;
				system("cls");
				for (int i = army1.units.size() - 1; i >= 0; i--)
				{
					cout << army1.getUnits()[i];
				}
				printSpace(4);
				for (int i = 0; i < units.size(); i++)
				{
					cout << units[i];
				}
				cout << endl;
				printSpace(army1.units.size() + 4 + index1);
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
	for (int i = army1.units.size() - 1; i >= 0; i--)
	{
		cout << army1.getUnits()[i];
	}
	printSpace(4);
	for (int i = 0, k = 0; i < units.size(); i++, k++)
	{
		if (k == index1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
			cout << units[i].getSymb();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			cout << units[i];
		}
	}
	cout << endl;
	printSpace(army1.units.size() + 4);
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
				for (int i = army1.units.size() - 1; i >= 0; i--)
				{
					cout << army1.getUnits()[i];
				}
				printSpace(4);
				for (int i = 0, k = 0; i < units.size(); i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i].getSymb();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}
				}
				cout << endl;
				printSpace(army1.units.size() +4 + index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}	


			break;
		}
		case 77:
		{
			if (index2 != units.size() - 1)
			{
				index2++;
				system("cls");
				for (int i = army1.units.size() - 1; i >= 0; i--)
				{
					cout << army1.getUnits()[i];
				}
				printSpace(4);
				for (int i = 0, k = 0; i < units.size(); i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i].getSymb();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else
					{
						cout << units[i];
					}
				}
				cout << endl;
				printSpace(army1.units.size() + 4 + index2);
				cout << '^';
				cout << "\nFirst unit index: " << index1;
				cout << "\nSecond unit index: " << index2;
				cout << "\nPress Enter to select the second unit to swap(the green one is selected).";
			}
			break;
		}
		}
	} while (isSelected == false);
}
void Army::swapUnits(int& index1,int& index2)
{
	index1 = 0;
	index2 = 0;
	if (units.size() < 2)
	{
		cout << "You have no enough units to swap\n";
		return;
	}
	system("cls");

	for (int i = 0; i < units.size(); i++)
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
				for (int i = 0; i < units.size(); i++)
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
			if (index1 != units.size() - 1)
			{
				index1++;
				system("cls");
				for (int i = 0; i < units.size(); i++)
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
	for (int i = 0, k = 0; i < units.size(); i++, k++)
	{
		if (k == index1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
			cout << units[i].getSymb();
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
				for (int i = 0, k = 0; i < units.size(); i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i].getSymb();
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
			if (index2 != units.size() - 1)
			{
				index2++;
				system("cls");
				for (int i = 0, k = 0; i < units.size(); i++, k++)
				{
					if (k == index1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
						cout << units[i].getSymb();
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
}

void Army::ArmySwap(int& index1, int& index2)
{
	swap(units[index1], units[index2]);
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
int Army::GetCapacity()
{
	return capacity;
}
int Army::getNumberOfUnits()
{
	return units.size();
}