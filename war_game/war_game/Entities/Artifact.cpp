#include"Artifact.h"

using namespace std;

Artifact::Artifact():
	type("default"),
	addPoints(1){}

Artifact::Artifact(string ttype, size_t aaddPoints):
	type(ttype),
	addPoints(aaddPoints){}

Artifact::Artifact(Artifact & a):
	type(a.type),
	addPoints(a.addPoints){}

string Artifact::getType()
{
	return type;
}

size_t Artifact::getAddPoints()
{
	return addPoints;
}


