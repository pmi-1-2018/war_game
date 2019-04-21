#include "Cell.h"
#include <ctime>



Cell::Cell() :
	passCost(1),
	isBarrier(true),
	x(0),
	y(0),
	barrack(nullptr)
{}
Cell::Cell(int passCost, int x, int y) :
	passCost(passCost),
//	isPlayer(false),
	isBarrier(true),
	barrack(nullptr)
{
	if (this->passCost == 0)
	{
		this->isBarrier = false;
	}
	this->x = x;
	this->y = y;

}

void Cell::setCell(char symb, int x, int y)
{
	int n = rand() % 6 + 1;
	this->y = x;
	this->x = y;
	this->barrack = nullptr;
	this->isBarrier = true;
	vector<Unit> units;
	Swordsman unit;
	switch (symb)
	{
	case '#':
		this->isBarrier = false;
		passCost = 0;
		break;
	case ' ':
		passCost = 1;
		break;
	case '2':
		passCost = 2;
		break;
	case '3':
		passCost = 3;
		break;
	case 'B':
		passCost = 1;
		this->isBarrack = true;
		this->isBarrier = true;
		
		if (n == 1)
		{
			this->barrack = new BarrackArcher();
		}
		else if (n == 2)
		{
			this->barrack = new BarrackSwordsman();
		}
		else if (n == 3)
		{

			this->barrack = new BarrackTank();
		}
		else if (n == 4)
		{
			this->barrack = new BarrackWizard();
		}
		else if (n == 5)
		{
			this->barrack = new BarrackBuffer();
		}
		else if (n == 6)
		{
			this->barrack = new BarrackHealer();
		}
		break;
	case 'A':
		passCost = 1;
		units.push_back(unit);
		//this->isBotArmy = true;
		this->army = new Army("Bot", units , 'A', false);
		this->isBarrier = true;
		break;
	default:
		passCost = 1;
		break;
	}
}
Barrack* Cell::getBarrackPtr()
{
	return barrack;
}

bool Cell::IsBarrack()
{
	return isBarrack;
}


Army* Cell::getArmyPtr()
{
	return army;
}
void Cell::setIsBotArmy(bool value)
{
	if (army != nullptr) 
	{
		this->army->setIsBotArmy(value);
	}
}
Cell::~Cell()
{
	if (this->army != nullptr)
	{
		if (this->playersCount == 1) {
			delete army;
		}
		else
		{
			delete[] army;
		}
	}
	if (this->barrack != nullptr)
	{
		delete barrack;
	}
}
int Cell::getPassCost()
{
	return passCost;
}
bool Cell::IsPlayer()
{
	if (this->army != nullptr)
	{
		return this->army->getIsPlayer();
	}
}
void Cell::SetPlayer(Army* army)
{
	this->army = army;
}
void Cell::SetBattleField(Army *players, const int & size)
{
	if (this->army != nullptr)
	{
		delete this->army;
	}
	this->army = new Army[size];
	this->playersCount = size;
	for (int i = 0; i < this->playersCount; i++)
	{
		this->army[i] = players[i];
	}
}
void Cell::setIsPlayer(bool val)
{
	this->army->setIsPlayer(val);
}
bool Cell::getIsPlayer()
{
	if (this->army != nullptr)
	{
		return this->army->getIsPlayer();
	}
	return false;
}
bool Cell::getIsBotArmy()
{
	if (this->army != nullptr)
	{
		return this->army->getIsBotArmy();
	}
	return false;
}
char Cell::GetArmySign()
{
	return this->army->GetSymb();
}
int Cell::GetArmyId()
{
	return this->army->GetId();
}
void Cell::SetArmy(Army * army)
{
	this->army = army;
}
Army * Cell::GetArmy()const
{
	return this->army;
}
Army* Cell::getArmyPtr()const
{
	return this->army;
}
bool Cell::IsPassable()
{
	return this->isBarrier;
}
void Cell::setPassCost(int value)
{
	this->passCost = value;
}
int Cell::GetX() const
{
	return this->x;
}
int Cell::GetY() const
{
	return this->y;
}
