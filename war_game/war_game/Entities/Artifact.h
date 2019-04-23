#pragma once
#include<iostream>
#include<string>

using namespace std;

class Artifact
{
protected:
	char symb;
	size_t addPoints;
	int invPosX;
	int invPosY;
	bool isActive;
	bool isSelected;
public:
	Artifact();
	Artifact(char ssymb, size_t aaddPoints);
	Artifact(Artifact & a);
	Artifact(char symb, int invPosX, int invPosY, bool isActive);
	char getSymb();
	size_t getAddPoints();
	int getInvPosX();
	int getInvPosY();
	bool getIsActive();
	bool getIsSelected();
	void setInvPosX(int invPosX);
	void setInvPosY(int invPosY);
	void setIsActive(bool isActive);
	void setIsSelected(bool isSelected);
};
