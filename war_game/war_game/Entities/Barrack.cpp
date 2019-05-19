#include"Barrack.h"

int Barrack::GetNumberOfUnits()
{
	return numberOfUnits;
}

void Barrack::SetNumberOfUnits(int number)
{
	this->numberOfUnits = number;
}

int Barrack::GetNumberOfTurn()
{
	return numberOfTurn;
}

void Barrack::SetNumberOfTurn(int number)
{
	this->numberOfTurn = number;
}

Unit Barrack::giveUnit()
{
	Unit unit;
	return unit;
}

string Barrack::TellType()
{
	return "Unit";
}
