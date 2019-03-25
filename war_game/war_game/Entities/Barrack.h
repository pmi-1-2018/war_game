#pragma once
#include"Army.h"
#include"Map.h"
#include "Swordsman.h"
#include "Tank.h"
#include "Wizard.h"

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


	void giveUnits(Army army);
	void renewal();
};

