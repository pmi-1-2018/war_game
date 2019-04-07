#include "Cell.h"


Cell::Cell() :
	passCost(1),
	isPassable(true),
	isPlayer(false),
	x(0),
	y(0),
	barrack(nullptr)
{}
Cell::Cell(int passCost, int x, int y) :
	passCost(passCost),
	isPlayer(false),
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
	this->y = y;
	this->x = x;
	this->isPlayer = false;
	this->barrack = nullptr;
	this->isPassable = true;
	Unit* list;
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
		this->isBarrack = true;
		this->isPassable = true;
		int n = rand(1, 4);
		switch (n)
		{
		case 1:
			this->barrack = new BarrackOfArchers();
			break;
		case 2:
			this->barrack = new BarrackOfSwordsmen();
			break;
		case 3:
			this->barrack = new BarrackOfTanks();
			break;
		case  4:
			this->barrack = new BarrackOfWizards();
			break;
		}
		break;
	case 'A':
		passCost = 1;
		list = new Unit[3];
		this->army = new Army("Bot", list, 3, 'A');
		this->isPassable = true;
		this->isBotArmy = true;
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
	return this->isPlayer;
}
void Cell::SetPlayer(bool val, Army* army)
{
	this->isPlayer = val;
	if (isPlayer == true)
	{
		this->army = army;
	}
	else
	{
		this->army = nullptr;
	}

}
void Cell::SetBattleField(Army *players, const int & size)
{
	if (this->army != nullptr)
	{
		delete army;
	}
	this->army = new Army[size];
	this->playersCount = size;
	for (int i = 0; i < this->playersCount; i++)
	{
		this->army[i] = players[i];
	}
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
void Cell::setIsPlayer(bool val)
{
	this->isPlayer = val;
}
bool Cell::getIsPlayer()
{
	return isPlayer;
}
bool Cell::getIsBotArmy()
{
	return isBotArmy;
}
