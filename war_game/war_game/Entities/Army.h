#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <vector>
#include <typeinfo>
#include "Windows.h"
#include "Unit.h"
#include "Swordsman.h"
#include "Tank.h"
#include "Archer.h"
#include "Buffer.h"
#include "Healer.h"
#include "Wizard.h"
#include "Artifact.h"
using namespace std;

static int counter = 0;
class Army
{
private:
	struct Inventory
	{
		struct ClipBoard
		{
			Artifact* item = nullptr;
			int posX;
			int posY;
		};
		int inventoryWidth;
		int inventoryHeight;
		Artifact*** artefacts;
		vector<Artifact> activeArtifacts;
		bool itemIsFixed = false;
		ClipBoard storage;
		int activeArtsNumber = 0;
		int maxActiveArtsNumber = 3;
		const HANDLE HSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
		vector<Artifact> getActiveArtifacts()const
		{
			return this->activeArtifacts;
		}
		bool AddArtifact(Artifact* element)
		{
			bool artAdded = false;
			for (int i = 0; i < this->inventoryWidth; i++)
			{
				for (int j = 0; j < this->inventoryHeight; j++)
				{
					if (this->artefacts[i][j] == nullptr)
					{
						artAdded = true;
						this->artefacts[i][j] = element;
						break;
					}
				}
				if (artAdded == true)
				{
					break;
				}
			}
			return artAdded;
		}
		bool RemoveActiveArtifact(Artifact& delArt)
		{
			bool artRemoved = false;
			for (int i = 0; i < this->activeArtsNumber; i++)
			{
				if (this->activeArtifacts.at(i) == delArt)
				{
					this->activeArtifacts.erase(this->activeArtifacts.begin() + i, this->activeArtifacts.begin() + i + 1);
					artRemoved = true;
					break;
				}
			}
			return artRemoved;
		}
		void RemoveArtifact(Artifact& artDel)
		{
			bool artDeleted = false;
			for (int i = 0; i < this->inventoryWidth; i++)
			{
				for (int j = 0; j < this->inventoryHeight; j++)
				{
					if (this->artefacts[i][j] != nullptr && *(this->artefacts[i][j]) == artDel)
					{
						if (this->artefacts[i][j]->getIsActive() == true)
						{
							RemoveActiveArtifact(artDel);
						}
						delete this->artefacts[i][j];
						this->artefacts[i][j] = nullptr;
					}
				}
			}
		}
		void SwapArtefact(int artIndX1, int artIndY1, int artIndX2, int artIndY2)
		{
			Artifact* tempPtr = this->artefacts[artIndY1][artIndX1];
			this->artefacts[artIndY1][artIndX1] = this->artefacts[artIndY2][artIndX2];
			this->artefacts[artIndY2][artIndX2] = tempPtr;
		}

		void PrintInventory(int& selectedX, int& selectedY, bool selectPressed, bool deleteArt = false)
		{
			SetConsoleTextAttribute(this->HSTDOUT, 240);
			cout << "|";
			for (int j = 0; j < this->inventoryWidth; j++)
			{
				cout << "*";
			}
			cout << "|" << endl;
			
			for (int i = 0; i < this->inventoryWidth; i++)
			{
				cout << "|";
				for (int j = 0; j < this->inventoryHeight; j++)
				{
					if (selectedY == i && selectedX == j)
					{
						// 96 - yellow
						SetConsoleTextAttribute(this->HSTDOUT, 64);
						if (this->artefacts[i][j] == nullptr)
						{
							cout << "-";
						}
						else
						{
							if (deleteArt == true) 
							{
								SetConsoleTextAttribute(this->HSTDOUT, 96);
							}
							else if (this->artefacts[i][j]->getIsActive() == true)
							{
								SetConsoleTextAttribute(this->HSTDOUT, 160);
							}
							cout << this->artefacts[i][j]->getSymb();
							SetConsoleTextAttribute(this->HSTDOUT, 64);
						}
						if (deleteArt == true)
						{
							RemoveArtifact(*this->storage.item);
						}
						if (selectPressed == true)
						{
							if (this->itemIsFixed == true)
							{
								Artifact* art1 = this->storage.item;
								Artifact* art2 = this->artefacts[i][j];
								if (art1 == art2)
								{
									if (art1 != nullptr && art1->getIsActive() == true)
									{
										art1->setIsActive(false);
										this->activeArtsNumber--;
										
										this->activeArtifacts.push_back(*art1);
									}
									else if (this->maxActiveArtsNumber >= this->activeArtsNumber + 1)
									{
										art1->setIsActive(true);
										this->activeArtsNumber++;
										this->activeArtifacts.push_back(*art1);
									}
								}
								else 
								{ 
									SwapArtefact(this->storage.posX, this->storage.posY, selectedX, selectedY);
								}
								
								SetConsoleTextAttribute(this->HSTDOUT, 240);
								if (art1 != nullptr)
								{
									art1->setIsSelected(false);
								}
								if (art2 != nullptr)
								{
									art2->setIsSelected(false);
								}
								this->itemIsFixed = false;
								SetConsoleTextAttribute(this->HSTDOUT, 15);
								system("cls");
								PrintInventory(selectedX, selectedY, false);
								return;
							}
							else
							{
								if (this->artefacts[i][j] != nullptr && this->artefacts[i][j]->getIsSelected() == false)
								{
									this->storage.item = this->artefacts[i][j];
									this->storage.posX = j;
									this->storage.posY = i;
									this->artefacts[i][j]->setIsSelected(true);
									this->itemIsFixed = true;
								}
							}
						}
					}
					else
					{
						if (this->artefacts[i][j] == nullptr)
						{
							cout << "-";
						}
						else
						{
							if (deleteArt == true)
							{
								SetConsoleTextAttribute(this->HSTDOUT, 96);
							}
							else if (this->artefacts[i][j]->getIsSelected() == true && this->itemIsFixed == true)
							{
								SetConsoleTextAttribute(this->HSTDOUT, 64);
							}
							else if (this->artefacts[i][j]->getIsActive() == true)
							{
								SetConsoleTextAttribute(this->HSTDOUT, 160);
							}
							cout << this->artefacts[i][j]->getSymb();
						}
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
			this->artefacts = new Artifact**[this->inventoryWidth];
			for (size_t i = 0; i < this->inventoryHeight; i++)
			{
				this->artefacts[i] = new Artifact*[this->inventoryWidth];
				for (size_t j = 0; j < this->inventoryWidth; j++)
				{
					this->artefacts[i][j] = nullptr;
				}
			}
		}
	};
	string nameOfArmy;
	vector<Unit> units;
	vector<Unit>::iterator it;
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
	int level;
	int experience;
	int capacity;
public:
	Army();
	Army(string name,vector<Unit> list, char symb, bool isPlayer, int wallet);

	void inputTheArmy(size_t sz); 
	void printArmiesFight(Army& a, bool shit);
	void printArmy();

	bool hit(Unit& u1,Unit& u2, vector<Artifact> thisArt, vector<Artifact> otherArt);
	void fight(Army& a,bool check);
	bool armyAutoAttack(Army& a);
	bool battlePVE(Army& a);
	bool battlePVP(Army& a);
	void heal();
	void buff();

	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsBotArmy();
	int getWallet();
	int getIncome();
	void setIsBotArmy(bool value);
	void increaseIncome(int value);
	void addMoneyToWallet(int value);


	Army& operator= (const Army& army);
	vector<Unit> getUnits();
	void CalcLevelAndCapacity(int countOfDead);
	void addUnit(Unit unit);

	void swapUnits_2(int & index1, int & index2, Army& army1);
	void swapUnits_1(int & index1, int & index2, Army& army2);
	void swapUnits(int& index1, int& index2);
	void ArmySwap(int& index1, int& index2);

	char GetSymb();
	int GetId();
	bool SetCurrEnergy(const int& value);
	int GetCurrEnergy();
	void InventoryMode();
	Inventory* getInventory()const
	{
		if (this->inventory != nullptr)
		{
			return this->inventory;
		}
		return nullptr;
	}
	int GetLevel();
	int GetExp();
	void SetLevel(int a);
	void SetCapacity(int a);
	int GetCapacity();
	int getNumberOfUnits();
	~Army()
	{
		if (this->inventory != nullptr) 
		{
			delete[] this->inventory;
		}
	}
};
