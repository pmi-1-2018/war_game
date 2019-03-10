#include "Cell.h"

Cell::Cell() :
	passCost(1),
	isPassable(true),
	x(0),
	y(0)
{}
Cell::Cell(int passCost, bool isPassable, int x, int y):
	passCost(passCost),
	isPassable(isPassable)
{
	if (isPassable == false)
	{
		passCost = 0;
	}
	this->x = x;
	this->y = y;
}
void Cell::setCell(char symb)
{
	isPassable = true;
	switch (symb)
	{
	case '#':
		isPassable = false;
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
