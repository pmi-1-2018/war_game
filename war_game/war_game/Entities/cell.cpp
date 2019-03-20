#include "Cell.h"


Cell::Cell() :
	passCost(1),
	isPassable(true),
	isPlayer(false),
	x(0),
	y(0)
{}
Cell::Cell(int passCost, int x, int y) :
	passCost(passCost),
	isPlayer(false),
	isPassable(true)
{
	if (this->passCost == 0)
	{
		this->isPassable = false;
	}
	this->x = x;
	this->y = y;

}

void Cell::setCell(char symb)
{
	switch (symb)
	{
	case '#':
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
	default:
		passCost = 0;
		break;
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
void Cell::SetPlayer(bool val, char symb)
{
	this->isPlayer = val;
	if (isPlayer == true) 
	{
		// Hard-coded array of 10 units. Probably, this function should take certain arguments to initialize the army.
		Unit units[10];
		this->army = new Army(to_string(symb), units, 10, symb);
	}
	else
	{
		army = nullptr;
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
bool Cell::IsPassable()
{
	return this->isPassable;
}
void Cell::setPassCost(int value)
{
	this->passCost = value;
}
void Cell::setIsPlayer(bool val)
{
	this->isPlayer = val;
}
bool Cell::getIsPlayer()
{
	return isPlayer;
}
