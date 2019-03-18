#pragma once
class Army 
{
	char symb;
public:
	Army(char symb) :symb(symb) {}
	char GetSymb() 
	{
		return this->symb;
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
	char GetArmy();
	bool IsPassable();
	void setPassCost(int value);

};

