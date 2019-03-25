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

void Barrack::giveUnits(Army army)
{
	int numberOfUnits;
	char letter;
	cout << "enter which units you want to take: ";
	switch (letter)
	{
	case 'S':
		cout << "enter how many swordsmen you want to take: ";
		cin >> numberOfUnits;
		if (numberOfUnits <= numberOfSwordsmen)
		{
			for (int i = 0; i < numberOfUnits; i++)
			{
				army.addUnit(Swordsman());
				army.SetCurrEnergy(-1);
			}
		}
		break;

	case 'A' :
		cout << "enter how many archers you want to take: ";
		cin >> numberOfUnits;
		if (numberOfUnits <= numberOfArchers)
		{
			for (int i = 0; i < numberOfUnits; i++)
			{
				army.addUnit(Archer());
				army.SetCurrEnergy(-1);
			}
		}
		break;
	case 'T' :
		cout << "enter how many tancs you want to take: ";
		cin >> numberOfUnits;
		if (numberOfUnits <= numberOfTanks)
		{
			for (int i = 0; i < numberOfUnits; i++)
			{
				army.addUnit(Tank());
				army.SetCurrEnergy(-1);
			}
		}
		break;
	case 'W' :
		cout << "enter how many wizards you want to take: ";
		cin >> numberOfUnits;
		if (numberOfUnits <= numberOfWizards)
		{
			for (int i = 0; i < numberOfUnits; i++)
			{
				army.addUnit(Wizard());
				army.SetCurrEnergy(-1);
			}
		}
		break;
	}
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