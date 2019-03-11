#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include"cell.h"


using namespace std;

class Map
{
private:
	int width;
	int height;
	Cell **map;
public:
	Map();
	void readMapFromFile(string fileName);
	void generateRandomMap(string fileName, int height, int width);
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	bool getIspassable(int a, int b);
	~Map();
	friend ostream& operator<<(ostream& sout, Map &m);
};

