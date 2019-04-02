#pragma once
#include "../Entities/Swordsman.h"
#include "../Entities/Tank.h"
#include "../Entities/Wizard.h"
#include "../Entities/Archer.h"

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
	virtual Unit* giveUnits();
	/*int GetNumberOfArchers();
	void SetNumberOfArchers(int number);
	int GetNumberOfTanks();
	void SetNumberOfTanks(int number);
	int GetNumberOfWizards();
	void SetNumberOfWizards(int number);*/
	

	void renewal();
};

