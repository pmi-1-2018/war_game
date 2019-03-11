#pragma once

class Cell
{
private:
	int passCost;
	bool isPassable;
	bool isPlayer;
public:
	Cell();
	Cell(int passCost);
	void setCell(char symb);
	int getPassCost();
	void setPassCost(int value);
	void setIsPlayer(bool val);
	bool getIsPlayer();
	bool getIsPassable()
	{
		return isPassable;
	}
};

