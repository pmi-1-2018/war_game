#include "Cell.h"
#include <ctime>



Cell::Cell() :
	passCost(1),
	isPassable(true),
	x(0),
	y(0),
	barrack(nullptr),
	goldMine(nullptr),
	artifact(nullptr)
{}

Cell::Cell(const Cell& other)
{
	this->passCost = other.passCost;
	this->isPassable = other.isPassable;
	this->barrack = other.barrack;
	this->isBarrack = other.isBarrack;
	this->army = other.army;
	this->goldMine = other.goldMine;
	this->playersCount = other.playersCount;
	this->artifact = other.artifact;
	this->x = other.x;
	this->y = other.y;
}

Cell::Cell(int passCost, int x, int y) :
	passCost(passCost),
//	isPlayer(false),
	isPassable(true),
	barrack(nullptr),
	goldMine(nullptr),
	artifact(nullptr)
{
	if (this->passCost == 0)
	{
		this->isPassable = false;
	}
	this->x = x;
	this->y = y;

}
// x - column, y - row
void Cell::setCell(char symb, int x, int y)// amount of X : width , amount of Y : height
{
	int n = rand() % 6 + 1;
	int quantity;
	this->y = y;
	this->x = x;
	this->barrack = nullptr;
	this->goldMine = nullptr;
	this->artifact = nullptr;
	this->isPassable = true;
	switch (symb)
	{
	case '#':
		this->isPassable = false;
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
	case 'B':
		passCost = 1;
		this->isBarrack = true;
		if (n == 1)
		{
			this->barrack = new BarrackArcher();
		}
		else if (n == 2)
		{
			this->barrack = new BarrackSwordsman();
		}
		else if (n == 3)
		{
			this->barrack = new BarrackTank();
		}
		else if (n == 4)
		{
			this->barrack = new BarrackWizard();
		}
		else if (n == 5)
		{
			this->barrack = new BarrackBuffer();
		}
		else if (n == 6)
		{
			this->barrack = new BarrackHealer();
		}
		break;
	case 'A':
		passCost = 1;
		quantity = rand() % 3 + 1;
		if (n == 1)
		{
			Archer a;
			vector<Unit> v(quantity, a);
			this->army = new Army("botsArchers", v, 'A', false, 50);
		}
		else if (n == 2)
		{
			Swordsman s;
			vector<Unit> v(quantity, s);
			this->army = new Army("BotsSwordsmans", v, 'A', false, 50);
		}
		else if (n == 3)
		{
			Tank t;
			vector<Unit> v(quantity, t);
			this->army = new Army("BotsTanks", v, 'A', false, 50);
		}
		else if (n == 4)
		{
			Wizard w;
			vector<Unit> v(quantity, w);
			this->army = new Army("BotsWizards", v, 'A', false, 50);
		}
		break;
	case 'G':
		passCost = 1;
		this->goldMine = new GoldMine();
		break;
	case '?':
		passCost = 1;
		this->artifact = new Artifact();
		break;
	default:
		passCost = 1;
		break;
	}
}

GoldMine* Cell::getGoldMinePtr()
{
	return goldMine;
}

bool Cell::isPossibleGenerate() 
{
	return this->artifact == nullptr && this->army == nullptr && this->barrack == nullptr && this->isPassable == true && this->goldMine == nullptr;
}

Barrack* Cell::getBarrackPtr()
{
	return barrack;
}

bool Cell::IsBarrack()
{
	return isBarrack;
}


Army* Cell::getArmyPtr()
{
	return army;
}
void Cell::setIsBotArmy(bool value)
{
	if (army != nullptr) 
	{
		this->army->setIsBotArmy(value);
	}
}
Cell::~Cell()
{
	if (this->army != nullptr)
	{
		if (this->playersCount == 1) {
			delete army;
		}
		else
		{
			delete[] army;
		}
	}
	if (this->barrack != nullptr)
	{
		delete barrack;
	}
}
int Cell::getPassCost()
{
	return passCost;
}
bool Cell::IsPlayer()
{
	if (this->army != nullptr)
	{
		return this->army->getIsPlayer();
	}
}
void Cell::SetPlayer(Army* army)
{
	this->army = army;
}
void Cell::SetBattleField(Army *players, const int & size)
{
	if (this->army != nullptr)
	{
		delete this->army;
	}
	this->army = new Army[size];
	this->playersCount = size;
	for (int i = 0; i < this->playersCount; i++)
	{
		this->army[i] = players[i];
	}
}
void Cell::setIsPlayer(bool val)
{
	this->army->setIsPlayer(val);
}
bool Cell::getIsPlayer()
{
	if (this->army != nullptr)
	{
		return this->army->getIsPlayer();
	}
	return false;
}
bool Cell::getIsBotArmy()
{
	if (this->army != nullptr)
	{
		return this->army->getIsBotArmy();
	}
	return false;
}
char Cell::GetArmySign()
{
	return this->army->GetSymb();
}
int Cell::GetArmyId()
{
	return this->army->GetId();
}
void Cell::SetArmy(Army * army)
{
	this->army = army;
}
Army * Cell::GetArmy()const
{
	return this->army;
}
Artifact * Cell::getArifactPtr()
{
	return this->artifact;
}
Army* Cell::getArmyPtr()const
{
	return this->army;
}
bool Cell::IsPassable()
{
	return this->isPassable;
}
void Cell::setPassCost(int value)
{
	this->passCost = value;
}
int Cell::GetX() const
{
	return this->x;
}
int Cell::GetY() const
{
	return this->y;
}
