#pragma once
#include<iostream>
#include<string>

using namespace std;

class Artifact
{
protected:
	string type;
	size_t addPoints;
public:
	Artifact();
	Artifact(string ttype, size_t aaddPoints);
	Artifact(Artifact & a);
	string getType();
	size_t getAddPoints();
};