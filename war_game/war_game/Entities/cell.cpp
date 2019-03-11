#include "Cell.h"

Cell::Cell() :
	passCost(1),
	isPassable(true),
	isPlayer(false)
{}
Cell::Cell(int passCost):
	passCost(passCost),
	isPassable(true)
{
	if (this->passCost == 0)
	{
		this->isPassable = false;
	}
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
		passCost = 1;
		break;
	}
}
int Cell::getPassCost()
{
	return passCost;
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
