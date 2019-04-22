#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "Windows.h"
#include "Unit.h"
#include "../Entities/Swordsman.h"
#include "../Entities/Tank.h"
#include "Archer.h"

using namespace std;

class Artefact 
{
public:
	char symb;
	bool isActive;
	bool isSelected;
	Artefact() 
	{
		this->isSelected = false;
		this->symb = '-';
		isActive = false;
	}

	Artefact(char symb, bool isActive) 
		:symb(symb), 
		isActive(isActive)
	{
		this->isSelected = false;
	}
};

static int counter = 0;
class Army
{
private:
	struct Inventory
	{
		int inventoryWidth;
		int inventoryHeight;
		Artefact*** artefacts;
		void PrintInventory(int& selectedX, int& selectedY);
		const HANDLE HSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
		
		void AddArtefact(int posX, int posY, Artefact* element)
		{
			if (posX < this->inventoryWidth && posY < this->inventoryHeight)
			{
				this->artefacts[posY][posX] = element;
			}
		}
		void SwapArtefact(int artIndX1, int artIndY1, int artIndX2, int artIndY2)
		{
			Artefact* tempPtr = this->artefacts[artIndY1][artIndX1];
			this->artefacts[artIndY1][artIndX1] = this->artefacts[artIndY2][artIndX2];
			this->artefacts[artIndY2][artIndX2] = tempPtr;
		}
		void PrintInventory(int& selectedX, int& selectedY, bool selectPressed)
		{
			SetConsoleTextAttribute(this->HSTDOUT, 240);
			cout << "|";
			for (int j = 0; j < this->inventoryWidth; j++)
			{
				cout << "*";
			}
			cout << "|" << endl;
			bool itemIsFixed = false;
			bool itemsSwapped = false;
			for (int i = 0; i < this->inventoryWidth; i++)
			{
				cout << "|";
				for (int j = 0; j < this->inventoryHeight; j++)
				{
					if (selectedY == i && selectedX == j)
					{
						SetConsoleTextAttribute(this->HSTDOUT, 64);
					}
					if (this->artefacts[i][j] == nullptr)
					{
						cout << "-";
						SetConsoleTextAttribute(this->HSTDOUT, 240);
						continue;
					}
					if (selectPressed == true)
					{
						if (this->artefacts[i][j]->isSelected == true)
						{
							Artefact* art1 = this->artefacts[selectedY][selectedX];
							Artefact* art2 = this->artefacts[i][j];
							SwapArtefact(selectedX, selectedY, j, i);
							SetConsoleTextAttribute(this->HSTDOUT, 240);
							if (art1 != nullptr) 
							{
								art1->isSelected = false;
							}
							if (art2 != nullptr)
							{
								art2->isSelected = false;
							}

						}
						else
						{
							if (itemIsFixed == false)
							{
								this->artefacts[i][j]->isSelected = true;
								itemIsFixed = true;
							}
						}
					}
					if (this->artefacts[i][j] != nullptr)
					{
						if (this->artefacts[i][j]->isSelected == true)
						{
							if (itemIsFixed == false)
							{
								SetConsoleTextAttribute(this->HSTDOUT, 64);
							}
						}
						cout << this->artefacts[i][j]->symb;
					}
					SetConsoleTextAttribute(this->HSTDOUT, 240);
				}
				cout << "|" << endl;
			}

			cout << "|";
			for (int j = 0; j < this->inventoryHeight; j++)
			{
				cout << "*";
			}
			cout << "|" << endl;
			SetConsoleTextAttribute(this->HSTDOUT, 15);
		}
		Inventory(int inventoryWidth, int inventoryHeight)
		{
			this->inventoryWidth = inventoryWidth;
			this->inventoryHeight = inventoryHeight;
			this->artefacts = new Artefact**[this->inventoryWidth];
			for (size_t i = 0; i < this->inventoryHeight; i++)
			{
				this->artefacts[i] = new Artefact*[this->inventoryWidth];
				for (size_t j = 0; j < this->inventoryWidth; j++)
				{
					this->artefacts[i][j] = nullptr;
				}
			}
		}
	};
	string nameOfArmy;
	Unit *units = nullptr;
	int numberOfUnits;
	char symb;
	int id;
	static const int START_ENERGY = 11;
	int dec_energy = 0;
	int currentEnergy;
	bool isPlayer = false;
	bool isBotArmy = false;
	int wallet;
	int income = 0;
	int stashSize = 2;
	Inventory* inventory = nullptr;
public:
	Army();
	Army(string name, Unit*list, int num, char symb, bool isPlayer, int money);
	void inputTheArmy();
	void printArmiesFight(Army& a, int thisArmy, int otherArmy, int incomingDamage, int outcomingDamage);
	void printArmies(Army& a, int thisArmy, int otherArmy);
	void printArmy();
	bool armyAutoAttack(Army& a);
	bool battlePVE(Army& a);
	bool battlePVP(Army& a);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	int getWallet();
	int getIncome();
	void setIsBotArmy(bool value);
	void increaseIncome(int value);
	void addMoneyToWallet(int value);
	Army& operator= (const Army& army);
	int getNumber();
	Unit* getWarriors();
	bool isDead(Unit unit);
	char GetSymb();
	int GetId();
	int getNumberOfUnits();
	void armyMove(Unit*list, int number);
	void addUnit(Unit unit);
	void swapUnits_2(int & index1, int & index2, Army& army1, int alive_count_army1, int alive_count_army2);
	void swapUnits_1(int & index1, int & index2, Army& army2, int alive_count_army1, int alive_count_army2);
	bool SetCurrEnergy(const int& value);
	int GetCurrEnergy();
	void InventoryMode();
	~Army()
	{
		if (this->units != nullptr) 
		{
			delete[] this->units;
		}
	}
};