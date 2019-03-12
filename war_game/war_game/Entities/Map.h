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
<<<<<<< HEAD
=======
	bool getIspassable(int a, int b);
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
	~Map();
	friend ostream& operator<<(ostream& sout, Map &m);
};

