#pragma once
static int counter = 0;
class Army 
{
	char symb;
	int id;

public:
	Army(char symb) :symb(symb) 
	{
		counter++;
		id = counter;
	}
	char GetSymb() 
	{
		return this->symb;
	}
	int GetId() 
	{
		return this->id;
	}
};
class Cell
{
private:
	int passCost;
	bool isPassable;
	bool isPlayer = false;
	Army* army;
	int x;
	int y;
public:
	Cell();
	Cell(int passCost, int x, int y);	
	void setCell(char symb);
	int getPassCost();
	bool IsPlayer();
	void SetPlayer(bool val, char symb);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	char GetArmySign();
	int GetArmyId();
	bool IsPassable();
	void setPassCost(int value);

};

