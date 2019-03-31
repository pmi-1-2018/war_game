#pragma once
#include "../Entities/Swordsman.h"
#include "../Entities/Tank.h"
#include "../Entities/Wizard.h"

class Barrack
{
protected:
	int numberOfUnits = 0;
	int numberOfTurn;
public:
	virtual int GetNumberOfUnits() = 0;
	virtual void SetNumberOfUnits(int number) = 0;
	virtual int GetNumberOfTurn() = 0;
	virtual void SetNumberOfTurn(int number) = 0;
	/*int GetNumberOfArchers();
	void SetNumberOfArchers(int number);
	int GetNumberOfTanks();
	void SetNumberOfTanks(int number);
	int GetNumberOfWizards();
	void SetNumberOfWizards(int number);*/
	

	void renewal();
};

