#include"Barrack.h"

int Barrack::GetNumberOfSwordsmen()
{
	return numberOfSwordsmen;
}

void Barrack::SetNumberOfSwordsmen(int number)
{
	this->numberOfSwordsmen = number;
}

int Barrack::GetNumberOfArchers()
{
	return numberOfArchers;
}

void Barrack::SetNumberOfArchers(int number)
{
	this->numberOfArchers = number;
}

int Barrack::GetNumberOfTanks()
{
	return numberOfTanks;
}

void Barrack::SetNumberOfTanks(int number)
{
	this->numberOfTanks = number;
}

int Barrack::GetNumberOfWizards()
{
	return numberOfWizards;
}

void Barrack::SetNumberOfWizards(int number)
{
	this->numberOfWizards = number;
}



int Barrack::GetNumberOfTurn()
{
	return numberOfTurn;
}


void Barrack::SetNumberOfTurn(int number)
{
	this->numberOfTurn = number;
}

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