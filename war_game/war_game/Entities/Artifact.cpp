#include"Artifact.h"

using namespace std;

Artifact::Artifact():
	symb('D'),
	addPoints(1),
	isActive(false),
	isSelected(false)
{}

Artifact::Artifact(char ssymb, size_t aaddPoints):
	symb(ssymb),
	addPoints(aaddPoints),
	isActive(false),
	isSelected(false)
{}

Artifact::Artifact(Artifact & a):
	symb(a.symb),
	addPoints(a.addPoints),
	isActive(a.isActive),
	isSelected(a.isActive)
{}

Artifact::Artifact(char symb, int invPosX, int invPosY, bool isActive):
	symb(symb),
	invPosX(invPosX),
	invPosY(invPosY),
	isActive(isActive),
	isSelected(false)
{}

char Artifact::getSymb()
{
	return this->symb;
}

size_t Artifact::getAddPoints()
{
	return addPoints;
}

int Artifact::getInvPosX()
{
	return this->invPosX;
}

int Artifact::getInvPosY()
{
	return this->invPosY;
}

bool Artifact::getIsActive()
{
	return this->isActive;
}

bool Artifact::getIsSelected()
{
	return this->isSelected;
}

void Artifact::setInvPosX(int invPosX)
{
	this->invPosX = invPosX;
}

void Artifact::setInvPosY(int invPosY)
{
	this->invPosY = invPosY;
}

void Artifact::setIsActive(bool isActive)
{
	this->isActive = isActive;
}

void Artifact::setIsSelected(bool isSelected)
{
	this->isSelected = isSelected;
}




