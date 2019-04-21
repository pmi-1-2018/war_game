#include"GoldMine.h"

GoldMine::GoldMine() :
	level(1),
	maxLvl(5),
	income(50),
	updateCost(200),
	owner('N'),
	pointerToOwner(nullptr)
{}

int GoldMine::getIncome()
{
	return this->income;
}

int GoldMine::getLvl()
{
	return this->level;
}

int GoldMine::getOwner()
{
	return this->owner;
}

Army* GoldMine::getPointerToOwner()
{
	return this->pointerToOwner;
}

void GoldMine::setPointerToOwner(Army* player)
{
	this->pointerToOwner = player;
}

void GoldMine::increaseLvl(int& vallet)
{
	if (vallet - updateCost >= 0)
	{
		if (level != maxLvl)
		{
			this->level++;
			this->income += 50;
			vallet -= updateCost;
			updateCost += 50;
			return;
		}
		else 
		{
			std::cout << "Your barrack is lvl " << maxLvl << "(max)." << std::endl;
		}
	}
	else
	{
		std::cout << "You need to have " << updateCost << " rupees to update this mine." << std::endl;
	}
}

void GoldMine::setOwner(char newOwnerSymb)
{
	this->owner = newOwnerSymb;
}

void GoldMine::giveGold(int& wallet)
{
	wallet += income;
}


