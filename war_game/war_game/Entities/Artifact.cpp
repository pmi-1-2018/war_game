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
{
	switch (symb)
	{
	case 'A':
		id = 1;
		break;
	case 'B':
		id = 2;
		break;
	default:
		id = 3;
		break;
	}
}

Artifact::Artifact(char ssymb, size_t aaddPoints, int pprice):
	symb(ssymb),
	addPoints(aaddPoints),
	isActive(false),
	isSelected(false),
	price(pprice)
{
	switch (symb)
	{
	case 'A':
		id = 1;
		break;
	case 'B':
		id = 2;
		break;
	default:
		id = 3;
		break;
	}
}

//Artifact::Artifact(Artifact & a):
//	symb(a.symb),
//	addPoints(a.addPoints),
//	isActive(a.isActive),
//	isSelected(a.isActive),
//	id(a.id),
//	price(a.price)
//{}

Artifact::Artifact(char symb, bool isActive):
	symb(symb),
	isActive(isActive),
	isSelected(false)
{
	switch (symb)
	{
	case 'A':
		id = 1;
		break;
	case 'B':
		id = 2;
		break;
	default:
		id = 3;
		break;
	}
}

bool Artifact::operator==(Artifact & compareArt)
{
	bool result = 
		this->id == compareArt.id &&
		this->symb == compareArt.symb &&
		this->addPoints == compareArt.addPoints &&
		this->isActive == compareArt.isActive &&
		this->isSelected == compareArt.isSelected &&
		this->price == compareArt.price;
	return result;
}

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
	cout << "ARTIFACT BONUS POINTS: " << this->addPoints << endl;
	cout << "PRICE: " << this->price << endl;
}






