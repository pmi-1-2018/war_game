#pragma once
#include "Swordsman.h"
#include "Tank.h"
#include "Wizard.h"
#include "Archer.h"
#include "Buffer.h"
#include "Healer.h"

class Barrack
{
protected:
	int numberOfUnits = 0;
	int numberOfTurn;
public:
	virtual int GetNumberOfUnits();
	virtual void SetNumberOfUnits(int number);
	virtual int GetNumberOfTurn();
	virtual void SetNumberOfTurn(int number);
	virtual Unit giveUnit();
	virtual int getCost();
	virtual string TellType();
};

