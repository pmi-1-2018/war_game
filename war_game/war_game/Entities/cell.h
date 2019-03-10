#pragma once

class Cell
{
private:
	int passCost;
	bool isPassable;
	int x;
	int y;
public:
	Cell();
	Cell(int passCost, bool isPassable, int x, int y);
	void setCell(char symb);
	int getPassCost();
	void setPassCost(int value);
};

