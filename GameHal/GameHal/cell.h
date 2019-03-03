#pragma once

class Cell
{
private:
	int passCost;
	bool isPassable;
public:
	Cell();
	Cell(int passCost, bool isPassable);
	void setCell(char symb);
	int getPassCost();
	void setPassCost(int value);
};

