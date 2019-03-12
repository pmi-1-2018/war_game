#include "Cell.h"

Cell::Cell() :
	passCost(1),
	isPassable(true),
<<<<<<< HEAD
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
=======
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
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
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
<<<<<<< HEAD
		passCost = 0;
=======
		passCost = 1;
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
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
<<<<<<< HEAD
=======
void Cell::setIsPlayer(bool val)
{
	this->isPlayer = val;
}
bool Cell::getIsPlayer()
{
	return isPlayer;
}
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
