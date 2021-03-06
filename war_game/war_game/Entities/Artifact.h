#pragma once
#include<iostream>
#include<string>

using namespace std;

class Artifact
{
protected:
	int id;
	char symb;
	size_t addPoints;
	bool isActive;
	bool isSelected;
	int price;
public:
	Artifact();
	Artifact(char ssymb, size_t aaddPoints);
	Artifact(char ssymb, size_t aaddPoints, int pprice);
	//Artifact(Artifact & a);
	Artifact(char symb, bool isActive);
	bool operator==(Artifact & compareArt);
	char getSymb();
	size_t getAddPoints();
	bool getIsActive();
	bool getIsSelected();
	void setIsActive(bool isActive);
	void setIsSelected(bool isSelected);
	void setId(int id);
	void printArtifactInfo();
};
