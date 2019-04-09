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

//int Barrack::GetNumberOfArchers()
//{
//	return numberOfArchers;
//}
//
//void Barrack::SetNumberOfArchers(int number)
//{
//	this->numberOfArchers = number;
//}
//
//int Barrack::GetNumberOfTanks()
//{
//	return numberOfTanks;
//}
//
//void Barrack::SetNumberOfTanks(int number)
//{
//	this->numberOfTanks = number;
//}
//
//int Barrack::GetNumberOfWizards()
//{
//	return numberOfWizards;
//}
//
//void Barrack::SetNumberOfWizards(int number)
//{
//	this->numberOfWizards = number;
//}



/*void Barrack::renewal()
{
	if (turnnum - GetNumberOfTurn() >= 5 && turnnum - GetNumberOfTurn() <= 10)
	{
		SetNumberOfSwordsmen(GetNumberOfSwordsmen() + 5);
		SetNumberOfArchers(GetNumberOfArchers() + 3);
		SetNumberOfTanks(GetNumberOfTanks() + 1);
		SetNumberOfWizards(GetNumberOfWizards() + 2);
	}
}*/