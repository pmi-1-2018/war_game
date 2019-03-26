#pragma once
#include "../Entities/Swordsman.h"
#include "../Entities/Tank.h"
#include "../Entities/Wizard.h"

class Barrack
{
protected:
	int numberOfSwordsmen;
	int numberOfArchers;
	int numberOfTanks;
	int numberOfWizards;
	int numberOfTurn;
public:
	int GetNumberOfSwordsmen();
	void SetNumberOfSwordsmen(int number);
	int GetNumberOfArchers();
	void SetNumberOfArchers(int number);
	int GetNumberOfTanks();
	void SetNumberOfTanks(int number);
	int GetNumberOfWizards();
	void SetNumberOfWizards(int number);
	
	int GetNumberOfTurn();
	void SetNumberOfTurn(int number);

	void renewal();
};

