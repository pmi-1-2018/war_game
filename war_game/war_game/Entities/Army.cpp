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

void Army::inputTheArmy() {
	char type;
	Swordsman s;
	Archer a;
	for (int i = 0; i < this->units.size(); i++) {
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
	vector<int> indexes(2, 0);
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
			this->selectUnits(false, indexes);
			swap(units[indexes[0]], units[indexes[1]]);
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
	int var = 0;
	vector<int> indexes(2, 0);
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
				this->selectUnits(false, indexes);
				swap(units[indexes[0]], units[indexes[1]]);
				this->buff();
				this->heal();
			}
			else
			{
				a.selectUnits(false, indexes);
				swap(a.units[indexes[0]], a.units[indexes[1]]);
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

void Army::buff()
{
	bool check = false;
	vector<int> indexes(2, 0);
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
	this->selectUnits(true,indexes);
	b.BuffDamage(units[indexes[0]]);
	b.BuffDefense(units[indexes[1]]);
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

void Army::selectUnits(bool isWithRepeats, vector<int>& indexes)
{
	if (units.size() < 2)
	{
		cout << "You have no enough units to swap\n";
		return;
	}
	system("cls");

	for (int i = 0; i < units.size(); i++)
	{
		cout << units[i].getSymb();
	}
	cout << endl;
	cout << '^';
	if (indexes.size() == 2)
	{
		cout << "\nFirst unit index: " << indexes[0];
		cout << "\nSecond unit index: ";
		cout << "\nPress Enter to select the first unit to swap.";
	}
	else
	{
		cout << "\nUnit index: " << indexes[0];
		cout << "\nPress Enter to select the unit to swap.";
	}



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
			if (indexes[0] != 0)
			{
				indexes[0]--;
				system("cls");
				for (int i = 0; i < units.size(); i++)
				{
					cout << units[i].getSymb();
				}
				cout << endl;
				printSpace(indexes[0]);
				cout << '^';
				if (indexes.size() == 2)
				{
					cout << "\nFirst unit index: " << indexes[0];
					cout << "\nSecond unit index: ";
					cout << "\nPress Enter to select the first unit to swap.";
				}
				else
				{
					cout << "\nUnit index: " << indexes[0];
					cout << "\nPress Enter to select the unit to swap.";
				}
			}


			break;
		}
		case 77:
		{
			if (indexes[0] != units.size() - 1)
			{
				indexes[0]++;
				system("cls");
				for (int i = 0; i < units.size(); i++)
				{
					cout << units[i].getSymb();
				}
				cout << endl;
				printSpace(indexes[0]);
				cout << '^';
				if (indexes.size() == 2)
				{
					cout << "\nFirst unit index: " << indexes[0];
					cout << "\nSecond unit index: ";
					cout << "\nPress Enter to select the first unit to swap.";
				}
				else
				{
					cout << "\nUnit index: " << indexes[0];
					cout << "\nPress Enter to select the unit to swap.";
				}
			}
			break;
		}
		}

	} while (isSelected == false);



	system("cls");
	if (indexes.size() == 2)
	{

		for (int i = 0, k = 0; i < units.size(); i++, k++)
		{
			if (k == indexes[0])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
				cout << units[i].getSymb();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				cout << units[i].getSymb();
			}
		}
		cout << endl;
		cout << '^';
		cout << "\nFirst unit index: " << indexes[0];
		cout << "\nSecond unit index: " << indexes[1];
		cout << "\nPress Enter to select the second unit to swap.";

		do
		{
			isSelected = false;
			switch (_getch())
			{
			case 13:
			{
				if (indexes[0] == indexes[1] && isWithRepeats == false)
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
				if (indexes[1] != 0)
				{
					indexes[1]--;
					system("cls");
					for (int i = 0, k = 0; i < units.size(); i++, k++)
					{
						if (k == indexes[0])
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
							cout << units[i].getSymb();
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
						else
						{
							cout << units[i].getSymb();
						}
					}
					cout << endl;
					printSpace(indexes[1]);
					cout << '^';
					cout << "\nFirst unit index: " << indexes[0];
					cout << "\nSecond unit index: " << indexes[1];
					cout << "\nPress Enter to select the second unit to swap.";
				}


				break;
			}
			case 77:
			{
				if (indexes[1] != units.size() - 1)
				{
					indexes[1]++;
					system("cls");
					for (int i = 0, k = 0; i < units.size(); i++, k++)
					{
						if (k == indexes[0])
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
							cout << units[i].getSymb();
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
						else
						{
							cout << units[i].getSymb();
						}
					}
					cout << endl;
					printSpace(indexes[1]);
					cout << '^';
					cout << "\nFirst unit index: " << indexes[0];
					cout << "\nSecond unit index: " << indexes[1];
					cout << "\nPress Enter to select the second unit to swap.";
				}
				break;
			}
			}
		} while (isSelected == false);
	}
	system("cls");
	if (indexes.size() == 2)
	{
		for (int i = 0; i < units.size(); i++)
		{
			if (i == indexes[0] && indexes[0] == indexes[1])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
				cout << units[i].getSymb();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (i == indexes[0])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
				cout << units[i].getSymb();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (i == indexes[1])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 103);
				cout << units[i].getSymb();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				cout << units[i].getSymb();
			}
		}
		cout << endl;
		cout << "\nFirst unit index: " << indexes[0];
		cout << "\nSecond unit index: " << indexes[1] << endl;
	}
	else
	{
		for (int i = 0; i < units.size(); i++)
		{
			if (i == indexes[0])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 39);
				cout << units[i].getSymb();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				cout << units[i].getSymb();
			}
		}
		cout << endl;
		cout << "\nUnit index: " << indexes[0] << endl;
	}

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