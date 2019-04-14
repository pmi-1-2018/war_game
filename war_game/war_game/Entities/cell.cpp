#include "Cell.h"


Cell::Cell() :
	passCost(1),
	isPassable(true),
	x(0),
	y(0),
	barrack(nullptr)
{}
Cell::Cell(int passCost, int x, int y) :
	passCost(passCost),
//	isPlayer(false),
	isPassable(true),
	barrack(nullptr)
{
	if (this->passCost == 0)
	{
		this->isPassable = false;
	}
	this->x = x;
	this->y = y;

}

void Cell::setCell(char symb, int x, int y)
{
	this->y = x;
	this->x = y;
	//this->isPlayer = false;
	this->barrack = nullptr;
	this->isPassable = true;
	Unit* units;
	switch (symb)
	{
	case '#':
		this->isPassable = false;
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
		this->barrack = new Barrack;
		this->isPassable = true;
		break;
	case 'A':
		passCost = 1;
		units = new Swordsman[1];
		//this->isBotArmy = true;
		this->army = new Army("Bot", units , 1, 'A', false);
		this->isPassable = true;
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
	if (this->barrack!=nullptr) 
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
	/*this->isPlayer = val;
	if (isPlayer == true) 
	{*/
	this->army = army;
	/*}
	else
	{
		this->army = nullptr;
	}*/
	
}
void Cell::SetBattleField(Army *players, const int & size)
{
	if (this->army != nullptr)
	{
		delete this->army;
	}
	this->army = new Army[size];
	this->playersCount = size;
	for (int i=0;i<this->playersCount; i++) 
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
Army * Cell::GetArmy(int& size)const
{
	size = this->playersCount;
	return this->army;
}
Army* Cell::getArmyPtr()const
{
	return this->army;
}
bool Cell::IsPassable()
{
	return this->isPassable;
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
