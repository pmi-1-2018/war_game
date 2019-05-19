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
	this->inventory = new Inventory(3, 3);
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



void Army::inputTheArmy(size_t size) {
	char type;
	Swordsman s;
	Archer a;
	Wizard w;
	Tank t;
	Buffer b;
	Healer h;
	for (size_t i = 0; i < size;i++) {
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




bool Army::armyAutoAttack(Army& a)
{
	int thisArmy = units.size();
	int otherArmy = a.units.size();
	bool check = true;
	system("CLS");
	int var = 0;
	this->printArmiesFight(a, var, var, var, var);
	do
	{
		this->buff();
		a.buff();
		this->heal();
		a.heal();
		this->fight(a,check);
		check = !check;
		sleep_for(seconds(2));
		if (units.size() != 0 && a.units.size() != 0)
		{
			a.fight(*this, check);
			check = !check;
			sleep_for(seconds(2));
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
		cout << "you won" << endl;
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
	this->printArmiesFight(a, var, var, var, var);
	do
	{
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
			sleep_for(seconds(2));
			if (units.size() != 0 && a.units.size() != 0)
			{
				a.fight(*this, check);
				check = !check;
				sleep_for(seconds(2));
			}
		}
		if (action == 'S' || action == 's')
		{
			this->swapUnits_1(index1, index2, a);
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
		cout << "you won" << endl;
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
	this->printArmiesFight(a, var, var, var, var);
	do
	{
		system("CLS");
		if (turn)
		{
			cout << "Attacker turn\n";
		}
		else
		{
			cout << "Defender turn\n";
		}
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
			sleep_for(seconds(3));
		}
		if (action == 'S' || action == 's')
		{
			if (turn == true)
			{
				this->swapUnits_1(index1, index2, a);
				swap(units[index1], units[index2]);
				this->buff();
				this->heal();
			}
			else
			{
				a.swapUnits_2(index1, index2, *this);
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
		cout << "you won" << endl;
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
		cout << "you lost" << endl;
		return false;
	}
}

void Army::fight(Army& a, bool check)
{
	it = units.begin();
	a.it = a.units.begin();
	int outcomingDamage = 0;
	int outcomingMagic = 0;
	int incomingMagic = 0;
	int incomingDamage = 0;
	if (units[0].getId() != 4)
	{
		outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
		if (outcomingDamage < 0)
		{
			outcomingDamage = 0;
		}
		if (units.size() >= 2)
		{
			if (units[1].getId() == 2)
			{
				outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
			}
		}
		if ((a.units[0].GetHealthPoints() - outcomingDamage) <= 0)
		{
			a.units.erase(a.it);
			a.it = a.units.begin();
		}
		else
		{
			a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingDamage);
		}
		if (a.units.size() != 0)
		{
			if (a.units[0].getId() != 4)
			{
				incomingDamage += a.units[0].GetDamage() - units[0].GetDefense();
				if (incomingDamage < 0)
				{
					incomingDamage = 0;
				}
				if ((units[0].GetHealthPoints() - incomingDamage) <= 0)
				{
					units.erase(it);
					it = units.begin();
				}
				else
				{
					units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingDamage);
				}
			}
			else
			{
				incomingMagic = a.units[0].GetDamage();
				if ((units[0].GetHealthPoints() - incomingDamage - incomingMagic) <= 0)
				{
					units.erase(it);
					it = units.begin();

					if (units.size() != 0)
					{
						if ((units[0].GetHealthPoints() - incomingMagic / 2) <= 0)
						{
							units.erase(it);
							it = units.begin();
							if (units.size() != 0)
							{
								if (units[0].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
						else
						{
							units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingMagic / 2);
							if (units.size() > 1)
							{
								if (units[1].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									it++;
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[1].SetHealthPoints(units[1].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
					}
				}
				else
				{
					units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingDamage - incomingMagic);
					if (units.size() > 1)
					{
						if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
						{
							it++;
							units.erase(it);
							it = units.begin();
							if (units.size() > 1)
							{
								if (units[1].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									it++;
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[1].SetHealthPoints(units[1].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
						else
						{
							units[1].SetHealthPoints(units[1].GetHealthPoints() - incomingMagic / 2);
							if (units.size() > 2)
							{
								if (units[2].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									it++;
									it++;
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[2].SetHealthPoints(units[2].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
					}
				}
			}
		}
		if (check == true)
		{
			this->printArmiesFight(a, incomingDamage, outcomingDamage, incomingMagic, outcomingMagic);
		}
		else
		{
			a.printArmiesFight(*this, outcomingDamage, incomingDamage, outcomingMagic, incomingMagic);
		}
	}
	else
	{
		if (units.size() >= 2)
		{
			if (units[1].getId() == 2)
			{
				outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
			}
		}
		outcomingMagic = units[0].GetDamage();
		if ((a.units[0].GetHealthPoints() - outcomingDamage - outcomingMagic) <= 0)
		{
			a.units.erase(a.it);
			a.it = a.units.begin();

			if (a.units.size() != 0)
			{
				if ((a.units[0].GetHealthPoints() - outcomingMagic / 2) <= 0)
				{
					a.units.erase(a.it);
					a.it = a.units.begin();
					if (a.units.size() != 0)
					{
						if (a.units[0].GetHealthPoints() - outcomingMagic / 4 <= 0)
						{
							a.units.erase(a.it);
							a.it = a.units.begin();
						}
						else
						{
							a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingMagic / 4);
						}
					}
				}
				else
				{
					a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingMagic / 2);
					if (a.units.size() > 1)
					{
						if (a.units[1].GetHealthPoints() - outcomingMagic / 4 <= 0)
						{
							a.it++;
							a.units.erase(a.it);
							a.it = a.units.begin();
						}
						else
						{
							a.units[1].SetHealthPoints(a.units[1].GetHealthPoints() - outcomingMagic / 4);
						}
					}
				}
			}
		}
		else
		{
			a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingDamage - outcomingMagic);
			if (a.units.size() > 1)
			{
				if ((a.units[1].GetHealthPoints() - outcomingMagic / 2) <= 0)
				{
					a.it++;
					a.units.erase(a.it);
					a.it = a.units.begin();
					if (a.units.size() > 1)
					{
						if (a.units[1].GetHealthPoints() - outcomingMagic / 4 <= 0)
						{
							a.it++;
							a.units.erase(a.it);
							a.it = a.units.begin();
						}
						else
						{
							a.units[1].SetHealthPoints(a.units[1].GetHealthPoints() - outcomingMagic / 4);
						}
					}
				}
				else
				{
					a.units[1].SetHealthPoints(a.units[1].GetHealthPoints() - outcomingMagic / 2);
					if (a.units.size() >= 3)
					{
						if (a.units[2].GetHealthPoints() - outcomingMagic / 4 <= 0)
						{
							a.it++;
							a.it++;
							a.units.erase(a.it);
							a.it = a.units.begin();
						}
						else
						{
							a.units[2].SetHealthPoints(a.units[2].GetHealthPoints() - outcomingMagic / 4);
						}
					}
				}
			}
		}
		if (a.units.size() != 0)
		{
			if (a.units[0].getId() != 4)
			{
				incomingDamage += a.units[0].GetDamage() - units[0].GetDefense();
				if (incomingDamage < 0)
				{
					incomingDamage = 0;
				}
				if ((units[0].GetHealthPoints() - incomingDamage) <= 0)
				{
					units.erase(it);
					it = units.begin();
				}
				else
				{
					units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingDamage);
				}
			}
			else
			{
				incomingMagic = a.units[0].GetDamage();
				if ((units[0].GetHealthPoints() - incomingDamage - incomingMagic) <= 0)
				{
					units.erase(it);
					it = units.begin();

					if (units.size() != 0)
					{
						if ((units[0].GetHealthPoints() - incomingMagic / 2) <= 0)
						{
							units.erase(it);
							it = units.begin();
							if (units.size() != 0)
							{
								if (units[0].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
						else
						{
							units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingMagic / 2);
							if (units.size() > 1)
							{
								if (units[1].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									it++;
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[1].SetHealthPoints(units[1].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
					}
				}
				else
				{
					units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingDamage - incomingMagic);
					if (units.size() > 1)
					{
						if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
						{
							it++;
							units.erase(it);
							it = units.begin();
							if (units.size() > 1)
							{
								if (units[1].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									it++;
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[1].SetHealthPoints(units[1].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
						else
						{
							units[1].SetHealthPoints(units[1].GetHealthPoints() - incomingMagic / 2);
							if (units.size() >= 3)
							{
								if (units[2].GetHealthPoints() - incomingMagic / 4 <= 0)
								{
									it++;
									it++;
									units.erase(it);
									it = units.begin();
								}
								else
								{
									units[2].SetHealthPoints(units[2].GetHealthPoints() - incomingMagic / 4);
								}
							}
						}
					}
				}
			}
		}
		if (check == true)
		{
			this->printArmiesFight(a, incomingDamage, outcomingDamage, incomingMagic, outcomingMagic);
		}
		else
		{
			a.printArmiesFight(*this, outcomingDamage, incomingDamage, outcomingMagic, incomingMagic);
		}
	}
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
	bool check = false;
	int index1, index2;
	Buffer b;
	for (size_t i = 0; i < units.size(); i++)
	{
		if (units[i].getId() == 5)
		{
			check = true;
			break;
		}
	}
	if (check == false)
	{
		return;
	}
	system("cls");
	this->swapUnits(index1,index2);
	b.BuffDamage(units[index1]);
	b.BuffDefense(units[index2]);
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

void Army::printArmiesFight(Army& a, int& incomingDamage, int& outcomingDamage, int& incomingMagic, int& outcomingMagic)
{
	system("CLS");
	if ((incomingDamage != 0 || incomingMagic != 0) && (outcomingDamage != 0 || outcomingMagic != 0))
	{
		if (outcomingMagic == 0 && incomingMagic == 0)
		{
			for (size_t i = 0; i < units.size(); i++)
			{
				cout << " ";
			}
			cout << "-" << incomingDamage << "  " << "-" << outcomingDamage << endl;
		}
		else if (incomingMagic != 0 && outcomingMagic == 0)
		{
			for (size_t i = 4; i < units.size(); i++)
			{
				cout << " ";
			}
			if (units.size() > 2)
			{
				cout << "-" << incomingMagic / 4;
			}
			if (units.size() > 1)
			{
				cout << "-" << incomingMagic / 2;
			}
			cout << '-' << incomingDamage + incomingMagic << "  " << "-" << outcomingDamage << endl;
		}
		else if (outcomingMagic == 0 && incomingMagic != 0)
		{
			for (size_t i = 4; i < units.size(); i++)
			{
				cout << " ";
			}
			cout << "-" << incomingDamage << "  " << "-" << outcomingDamage + outcomingMagic;
			if (a.units.size() > 1)
			{
				cout << "-" << outcomingMagic / 2;
			}
			if (a.units.size() > 2)
			{
				cout << "-" << outcomingMagic / 4;
			}
			cout << endl;

		}
		else if (outcomingMagic != 0 && incomingMagic != 0)
		{
			for (size_t i = 4; i < units.size(); i++)
			{
				cout << " ";
			}
			if (units.size() > 2)
			{
				cout << "-" << incomingMagic / 4;
			}
			if (units.size() > 1)
			{
				cout << "-" << incomingMagic / 2;
			}
			cout << "-" << incomingMagic + incomingDamage << "  " << "-" << outcomingDamage + outcomingMagic;
			if (a.units.size() > 1)
			{
				cout << "-" << outcomingMagic / 2;
			}
			if (a.units.size() > 2)
			{
				cout << "-" << outcomingMagic / 4;
			}
			cout << endl;
		}
	}
	for (size_t i = 0; i < units.size(); i++)
	{
		cout << units[units.size() - i - 1] << " ";
	}
	cout << "     ";
	for (size_t i = 0; i < a.units.size(); i++)
	{
		cout << a.units[i] << " ";
	}
	cout << endl;
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
void Army::DelBonTime()
{
	bonus.delBonTime(1);
}
int Army::GetBonusTime()
{
	return bonus.getBonTime();
}
void Army::AddBonus()
{
	bonus.BonusDamage(units);
	bonus.BonusHP(units);
	CalcLevelAndCapacity(bonus.getBonusExp());
	addMoneyToWallet(bonus.getBonusGold());
	bonus.setBonTime(21);
}
void Army::DelBonus()
{
	bonus.DelBonusDamage(units);
	bonus.DelBonusHP(units);
	
	bonus.setBonTime(-1);

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