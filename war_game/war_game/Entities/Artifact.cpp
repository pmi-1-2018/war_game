#include"Artifact.h"

using namespace std;

Artifact::Artifact():
	symb('-'),
	addPoints(1),
	isActive(false),
	isSelected(false),
	id(0),
	price(0)
{}

Artifact::Artifact(char ssymb, size_t aaddPoints):
	symb(ssymb),
	addPoints(aaddPoints),
	isActive(false),
	isSelected(false),
	price(aaddPoints*3)
{}

Artifact::Artifact(char ssymb, size_t aaddPoints, int pprice):
	symb(ssymb),
	addPoints(aaddPoints),
	isActive(false),
	isSelected(false),
	price(pprice)
{}

Artifact::Artifact(Artifact & a):
	symb(a.symb),
	addPoints(a.addPoints),
	isActive(a.isActive),
	isSelected(a.isActive),
	id(a.id)
{}

Artifact::Artifact(char symb, bool isActive):
	symb(symb),
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

bool Artifact::getIsActive()
{
	return this->isActive;
}

bool Artifact::getIsSelected()
{
	return this->isSelected;
}

void Artifact::setIsActive(bool isActive)
{
	this->isActive = isActive;
}

void Artifact::setIsSelected(bool isSelected)
{
	this->isSelected = isSelected;
}

void Artifact::setId(int id)
{
	this->id = id;
}

void Artifact::printArtifactInfo()
{
	cout << "TYPE: ";
	char type = this->symb;
	switch (type)
	{
	case 'A':
	{
		cout << "Attacking artifact" << endl;
		break;
	}
	case 'D':
	{
		cout << "Defensive artifact" << endl;
		break;
	}
	case 'E':
	{
		cout << "Energy artifact" << endl;
		break;
	}
	default:
		break;
	}
	cout << "EXTRA POINTS: " << this->addPoints << endl;
	cout << "VALUE: " << this->price << endl;
}






