#pragma once

class Cell
{
private:
	int passCost;
	bool isPassable;
<<<<<<< HEAD
	int x;
	int y;
public:
	Cell();
	Cell(int passCost, bool isPassable, int x, int y);
	void setCell(char symb);
	int getPassCost();
	void setPassCost(int value);
=======
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
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
};

