#include "Cell.h"

Cell::Cell() :
	passCost(1),
	isPassable(true),
	isPlayer(false),
	x(0),
	y(0)
{}
Cell::Cell(int passCost, int x, int y):
	passCost(passCost),
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
		this->army = new Army(symb);
	}
	else
	{
		army = nullptr;
	}
	
}
char Cell::GetArmy()
{
	return this->army->GetSymb();
}
bool Cell::IsPassable()
{
	return this->isPassable;
}
void Cell::setPassCost(int value)
{
	this->passCost = value;
}
