#include <string>
#include <typeinfo>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include "Army.h"


using namespace std::this_thread;
using namespace std::chrono;

Army::Army() :nameOfArmy("default") {}
Army::Army(string name, vector<Unit> list, char symb, bool isPlayer)
{
	nameOfArmy = name;
	this->units = list;
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
	it = units.begin();
	a.it = a.units.begin();
	int outcomingDamage;
	double outcomingMagic = 0;
	double incomingMagic = 0;
	int incomingDamage;
	system("CLS");
	this->printArmies(a);
	do
	{
		if (units[0].getId() != 4 && a.units[0].getId() != 4)// if there are no wizards 
		{
			outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
			if (units.size() >= 2)
			{
				if (units[1].getId() == 2)
				{
					outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
				}
			}
			if (outcomingDamage < 0)
			{
				outcomingDamage = 0;
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
				incomingDamage = a.units[0].GetDamage() - units[0].GetDefense();
				if (a.units.size() >= 2)
				{
					if (a.units[1].getId() == 2)
					{
						incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
					}
				}
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
			this->printArmiesFight(a, incomingDamage, outcomingDamage);
		}
		else if(units[0].getId() == 4 && a.units[0].getId() != 4) // if wizard is in the left army
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
						if (a.units.size() >= 1)
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
				if (a.units.size() >= 1)
				{
					if ((a.units[1].GetHealthPoints() - outcomingMagic / 2) <= 0)
					{
						a.it++;
						a.units.erase(a.it);
						a.it = a.units.begin();
						if (a.units.size() >= 1)
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
						if (a.units.size() >= 2)
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
			this->printArmyWizardLeft(a, outcomingMagic, incomingDamage, outcomingDamage);
		}
		else if (units[0].getId() != 4 && units[0].getId() == 4) // wizard in right army
		{
			outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
			if (units.size() >= 2)
			{
				if (units[1].getId() == 2)
				{
					outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
				}
			}
			if (outcomingDamage < 0)
			{
				outcomingDamage = 0;
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
				if (a.units.size() >= 2)
				{
					if (a.units[1].getId() == 2)
					{
						incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
					}
				}
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
							if (units.size() >= 1)
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
					if (units.size() >= 1)
					{
						if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
						{
							it++;
							units.erase(it);
							it = units.begin();
							if (units.size() >= 1)
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
							if (units.size() >= 2)
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
				this->printArmyWizardRight(a, incomingMagic, incomingDamage, outcomingDamage);
			}
		}
		else // if there are wizards in both armies
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
						if (a.units.size() >= 1)
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
				if (a.units.size() >= 1)
				{
					if ((a.units[1].GetHealthPoints() - outcomingMagic / 2) <= 0)
					{
						a.it++;
						a.units.erase(a.it);
						a.it = a.units.begin();
						if (a.units.size() >= 1)
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
						if (a.units.size() >= 2)
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
			outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
			if (units.size() >= 2)
			{
				if (units[1].getId() == 2)
				{
					outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
				}
			}
			if (outcomingDamage < 0)
			{
				outcomingDamage = 0;
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
				if (a.units.size() >= 2)
				{
					if (a.units[1].getId() == 2)
					{
						incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
					}
				}
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
							if (units.size() >= 1)
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
					if (units.size() >= 1)
					{
						if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
						{
							it++;
							units.erase(it);
							it = units.begin();
							if (units.size() >= 1)
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
							if (units.size() >= 2)
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
			this->printArmyWizardBoth(a, incomingMagic, outcomingMagic, incomingDamage, outcomingDamage);
		}
		sleep_for(seconds(1));
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
	double outcomingMagic = 0;
	double incomingMagic = 0;
	double incomingDamage = 0;
	int thisArmy = units.size();
	int otherArmy = a.units.size();
	char action;
	int index1 = 0;
	int index2 = 0;
	system("CLS");
	this->printArmies(a);
	do
	{
		cout << "press A to attack, press S to swap";
		action = _getch();
		if (action == 'A' || action == 'a')
		{
			if (units[0].getId() != 4 && a.units[0].getId() != 4)// if there are no wizards 
			{
				outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
				if (units.size() >= 2)
				{
					if (units[1].getId() == 2)
					{
						outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
					}
				}
				if (outcomingDamage < 0)
				{
					outcomingDamage = 0;
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
					incomingDamage = a.units[0].GetDamage() - units[0].GetDefense();
					if (a.units.size() >= 2)
					{
						if (a.units[1].getId() == 2)
						{
							incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
						}
					}
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
				this->printArmiesFight(a, incomingDamage, outcomingDamage);
			}
			else if (units[0].getId() == 4 && a.units[0].getId() != 4) // if wizard is in the left army
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
							if (a.units.size() >= 1)
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
					if (a.units.size() >= 1)
					{
						if ((a.units[1].GetHealthPoints() - outcomingMagic / 2) <= 0)
						{
							a.it++;
							a.units.erase(a.it);
							a.it = a.units.begin();
							if (a.units.size() >= 1)
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
							if (a.units.size() >= 2)
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
				this->printArmyWizardLeft(a, outcomingMagic, incomingDamage, outcomingDamage);
			}
			else if (units[0].getId() != 4 && units[0].getId() == 4) // wizard in right army
			{
				outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
				if (units.size() >= 2)
				{
					if (units[1].getId() == 2)
					{
						outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
					}
				}
				if (outcomingDamage < 0)
				{
					outcomingDamage = 0;
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
					if (a.units.size() >= 2)
					{
						if (a.units[1].getId() == 2)
						{
							incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
						}
					}
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
								if (units.size() >= 1)
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
						if (units.size() >= 1)
						{
							if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
							{
								it++;
								units.erase(it);
								it = units.begin();
								if (units.size() >= 1)
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
								if (units.size() >= 2)
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
					this->printArmyWizardRight(a, incomingMagic, incomingDamage, outcomingDamage);
				}
			}
			else // if there are wizards in both armies
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
							if (a.units.size() >= 1)
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
					if (a.units.size() >= 1)
					{
						if ((a.units[1].GetHealthPoints() - outcomingMagic / 2) <= 0)
						{
							a.it++;
							a.units.erase(a.it);
							a.it = a.units.begin();
							if (a.units.size() >= 1)
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
							if (a.units.size() >= 2)
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
				outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
				if (units.size() >= 2)
				{
					if (units[1].getId() == 2)
					{
						outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
					}
				}
				if (outcomingDamage < 0)
				{
					outcomingDamage = 0;
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
					if (a.units.size() >= 2)
					{
						if (a.units[1].getId() == 2)
						{
							incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
						}
					}
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
								if (units.size() >= 1)
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
						if (units.size() >= 1)
						{
							if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
							{
								it++;
								units.erase(it);
								it = units.begin();
								if (units.size() >= 1)
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
								if (units.size() >= 2)
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
				this->printArmyWizardBoth(a, incomingMagic, outcomingMagic, incomingDamage, outcomingDamage);
			}
		}
		if (action == 'S' || action == 's')
		{
			this->swapUnits_1(index1, index2, a);
			swap(units[index1], units[index2]);

			if (a.units[0].getId() != 4)
			{
				incomingDamage = a.units[otherArmy].GetDamage() - units[thisArmy].GetDefense();
				if (a.units.size() >= 2)
				{
					if (a.units[1].getId() == 2)
					{
						incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
					}
				}
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
				system("CLS");
				this->printArmiesFight(a, incomingDamage, outcomingDamage);
			}
			else // wizard in right army
			{
				outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
				if (units.size() >= 2)
				{
					if (units[1].getId() == 2)
					{
						outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
					}
				}
				if (outcomingDamage < 0)
				{
					outcomingDamage = 0;
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
					if (a.units.size() >= 2)
					{
						if (a.units[1].getId() == 2)
						{
							incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
						}
					}
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
								if (units.size() >= 1)
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
						if (units.size() >= 1)
						{
							if ((units[1].GetHealthPoints() - incomingMagic / 2) <= 0)
							{
								it++;
								units.erase(it);
								it = units.begin();
								if (units.size() >= 1)
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
								if (units.size() >= 2)
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
					this->printArmyWizardRight(a, incomingMagic, incomingDamage, outcomingDamage);
				}
			}
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
//bool Army::battlePVP(Army& a)
//{
//	int incomingMagic = 0;
//	int outcomingMagic = 0;
//	double outcomingDamage = 0;
//	double incomingDamage = 0;
//	int thisArmy = units.size();
//	int otherArmy = a.units.size();
//	char action;
//	int index1 = 0;
//	int index2 = 0;
//	system("CLS");
//	this->printArmies(a);
//	do
//	{
//		cout << "press A to attack, press S to swap";
//		action = _getch();
//		if (action == 'A' || action == 'a')
//		{
//			if (units[0].getId() != 4)
//			{
//				outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
//				if (units.size() >= 2)
//				{
//					if (units[1].getId() == 2)
//					{
//						outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
//					}
//				}
//				if (outcomingDamage < 0)
//				{
//					outcomingDamage = 0;
//				}
//				if ((a.units[0].GetHealthPoints() - outcomingDamage) <= 0)
//				{
//					a.units.erase(a.it);
//					a.it = a.units.begin();
//				}
//				else
//				{
//					a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingDamage);
//
//				}
//				if (a.units.size() != otherArmy)
//				{
//					incomingDamage = a.units[0].GetDamage() - units[0].GetDefense();
//					if (incomingDamage < 0)
//					{
//						incomingDamage = 0;
//					}
//					if ((units[0].GetHealthPoints() - incomingDamage) <= 0)
//					{
//						units.erase(it);
//						it = units.begin();
//					}
//					else
//					{
//						units[thisArmy].SetHealthPoints(units[thisArmy].GetHealthPoints() - incomingDamage);
//					}
//				}
//				system("CLS");
//				this->printArmiesFight(a, incomingDamage, outcomingDamage);
//			}
//			else
//			{
//				if (units.size() >= 2)
//				{
//					if (units[1].getId() == 2)
//					{
//						outcomingDamage += units[1].GetDamage() - a.units[0].GetDefense();
//					}
//				}
//				outcomingMagic = units[0].GetDamage();
//				if ((a.units[0].GetHealthPoints() - outcomingDamage - outcomingMagic) <= 0)
//				{
//					a.units.erase(a.it);
//					a.it = a.units.begin();
//
//					if (a.units.size() != 0)
//					{
//						if ((a.units[0].GetHealthPoints() - outcomingMagic / 2) <= 0)
//						{
//							a.units.erase(a.it);
//							a.it = a.units.begin();
//							if (a.units.size() != 0)
//							{
//								if (a.units[0].GetHealthPoints() - outcomingMagic / 4 <= 0)
//								{
//									a.units.erase(a.it);
//									a.it = a.units.begin();
//								}
//								else
//								{
//									a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingMagic / 4);
//								}
//							}
//						}
//						else
//						{
//							a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingMagic / 2);
//							if (a.units.size() >= 1)
//							{
//								if (a.units[1].GetHealthPoints() - outcomingMagic / 4 <= 0)
//								{
//									a.it++;
//									a.units.erase(a.it);
//									a.it = a.units.begin();
//								}
//								else
//								{
//									a.units[1].SetHealthPoints(a.units[1].GetHealthPoints() - outcomingMagic / 4);
//								}
//							}
//						}
//					}
//				}
//				else
//				{
//					a.units[0].SetHealthPoints(a.units[0].GetHealthPoints() - outcomingDamage - outcomingMagic);
//					if (a.units.size() >= 1)
//					{
//						if ((a.units[1].GetHealthPoints() - outcomingMagic / 2) <= 0)
//						{
//							a.it++;
//							a.units.erase(a.it);
//							a.it = a.units.begin();
//							if (a.units.size() >= 1)
//							{
//								if (a.units[1].GetHealthPoints() - outcomingMagic / 4 <= 0)
//								{
//									a.it++;
//									a.units.erase(a.it);
//									a.it = a.units.begin();
//								}
//								else
//								{
//									a.units[1].SetHealthPoints(a.units[1].GetHealthPoints() - outcomingMagic / 4);
//								}
//							}
//						}
//						else
//						{
//							a.units[1].SetHealthPoints(a.units[1].GetHealthPoints() - outcomingMagic / 2);
//							if (a.units.size() >= 2)
//							{
//								if (a.units[2].GetHealthPoints() - outcomingMagic / 4 <= 0)
//								{
//									a.it++;
//									a.it++;
//									a.units.erase(a.it);
//									a.it = a.units.begin();
//								}
//								else
//								{
//									a.units[2].SetHealthPoints(a.units[2].GetHealthPoints() - outcomingMagic / 4);
//								}
//							}
//						}
//					}
//				}
//				this->printArmyWizardLeft(a, outcomingMagic, incomingDamage, outcomingDamage);
//			}
//		}
//		else
//		{
//			this->swapUnits_1(index1, index2, a);
//			swap(units[index1], units[index2]);
//			system("CLS");
//			this->printArmies(a);
//		}
//		if (units.size() != 0 && a.units.size() != 0)
//		{
//			cout << "\npress A to attack, press S to swap";
//			action = _getch();
//			if (action == 'A' || action == 'a')
//			{
//				incomingDamage = a.units[0].GetDamage() - units[0].GetDefense();
//				if (a.units.size() >= 2)
//				{
//					if (a.units[1].getId() == 2)
//					{
//						incomingDamage += a.units[1].GetDamage() - units[0].GetDefense();
//					}
//				}
//				if (incomingDamage < 0)
//				{
//					incomingDamage = 0;
//				}
//				if ((units[0].GetHealthPoints() - incomingDamage) <= 0)
//				{
//					units.erase(it);
//					it = units.begin();
//				}
//				else
//				{
//					units[0].SetHealthPoints(units[0].GetHealthPoints() - incomingDamage);
//				}
//				if (units.size() != 0)
//				{
//					outcomingDamage = units[0].GetDamage() - a.units[0].GetDefense();
//					if (outcomingDamage < 0)
//					{
//						outcomingDamage = 0;
//					}
//					if ((a.units[0].GetHealthPoints() - outcomingDamage) <= 0)
//					{
//						a.units.erase(a.it);
//						a.it = a.units.begin();
//					}
//					else
//					{
//						a.units[otherArmy].SetHealthPoints(a.units[otherArmy].GetHealthPoints() - outcomingDamage);
//					}
//					system("CLS");
//					this->printArmiesFight(a, thisArmy, otherArmy, incomingDamage, outcomingDamage);
//				}
//			}
//			else
//			{
//				a.swapUnits_2(index1, index2, *this, numberOfUnits - thisArmy, a.numberOfUnits - otherArmy);
//				swap(a.units[index1], a.units[index2]);
//				system("CLS");
//				this->printArmies(a, thisArmy, otherArmy);
//			}
//		}
//	} while (numberOfUnits != thisArmy && a.numberOfUnits != otherArmy);
//	if (otherArmy == a.numberOfUnits)
//	{
//		delete[] a.units;
//		Unit* copy = new Unit[5];
//		CalcLevelAndCapacity(otherArmy);
//		for (size_t i = 0; i < numberOfUnits - thisArmy; i++)
//		{
//			copy[i] = units[i + thisArmy];
//		}
//		delete[] units;
//		units = copy;
//		numberOfUnits -= thisArmy;
//		dec_energy = 0;
//		for (size_t i = 0; i < numberOfUnits; i++)
//		{
//			dec_energy += units[i].GetDecEnergy();
//		}
//		cout << endl << symb << "  won" << endl;
//		this->printArmy();
//		return true;
//	}
//	if (thisArmy == numberOfUnits)
//	{
//		delete[] units;
//		Unit* copy = new Unit[5];
//		CalcLevelAndCapacity(thisArmy);
//		for (size_t i = 0; i < a.numberOfUnits - otherArmy; i++)
//		{
//			copy[i] = a.units[i + otherArmy];
//		}
//		delete[] a.units;
//		a.units = copy;
//		a.numberOfUnits -= otherArmy;
//		a.dec_energy = 0;
//		for (size_t i = 0; i < a.numberOfUnits; i++)
//		{
//			a.dec_energy += a.units[i].GetDecEnergy();
//		}
//		cout << endl << a.symb << "  won" << endl;
//		a.printArmy();
//		return false;
//	}
//}

void Army::printArmy()
{
	for (int i = 0; i < units.size(); i++)
	{
		cout << this->units[i];
	}
	cout << endl;
	system("pause");
}

void Army::printArmiesFight(Army& a, int incomingDamage, int outcomingDamage)
{
	system("CLS");
	for (size_t i = 2; i < units.size(); i++)
	{
		cout << " ";
	}
	cout << "-" << incomingDamage << "  " << "-" << outcomingDamage << endl;
	for (size_t i = 0; i < units.size(); i++)
	{
		cout << units[units.size() - i - 1];
	}
	cout << "     ";
	for (size_t i = 0; i < a.units.size(); i++)
	{
		cout << a.units[i];
	}
	cout << endl;
}

void Army::printArmyWizardLeft(Army& a, int outcomingMagic, int incomingDamage, int outcomingDamage)
{
	system("CLS");
	for (size_t i = 4; i < units.size(); i++)
	{
		cout << " ";
	}
	cout << "-" << incomingDamage << "  " << "-" << outcomingDamage + outcomingMagic << "-" << outcomingMagic / 2 << "-" << outcomingMagic / 4 << endl;
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


void Army::printArmyWizardBoth(Army& a, int incomingMagic, int outcomingMagic, int incomingDamage, int outcomingDamage)
{
	system("CLS");
	for (size_t i = 4; i < units.size(); i++)
	{
		cout << " ";
	}
	cout << "-" << incomingMagic / 4 << '-' << incomingMagic / 2 << "-" << incomingMagic + incomingDamage << "  " 
		<< "-" << outcomingDamage + outcomingMagic << "-" << outcomingMagic /2 << "-" << outcomingMagic /4 << endl;
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


void Army::printArmyWizardRight(Army& a, int incomingMagic, int incomingDamage, int outcomingDamage)
{
	system("CLS");
	for (size_t i = 4; i < units.size(); i++)
	{
		cout << " ";
	}
	cout << "-" << incomingMagic / 4 << '-' << incomingMagic / 2 << '-' << incomingDamage + incomingMagic << "  " << "-" << outcomingDamage << endl;
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

void Army::printArmies(Army& a)
{
	for (size_t i = 0; i < units.size(); i++)
	{
		cout << units[units.size() - i - 1];
	}
	cout << "     ";
	for (size_t i = 0; i < a.units.size(); i++)
	{
		cout << a.units[i + units.size()];
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


void Army::swapUnits()
{
	if (units.size() < 2)
	{
		cout << "You have no enough units to swap\n";
		return;
	}
	system("cls");
	int index1 = 0;
	int index2 = 0;

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

//bool Army::CheckCapacity()
//{
//	if (numberOfUnits < capacity)
//	{
//		cout << "You can add " << capacity - numberOfUnits << " units" << endl;
//		return true;
//	}
//	if (numberOfUnits == capacity)
//	{
//		cout << "You cann't add units" << endl;
//		return false;
//	}
//}
int Army::GetCapacity()
{
	return capacity;
}

