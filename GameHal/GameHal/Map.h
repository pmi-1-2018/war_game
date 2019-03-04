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
	void printMapIntoFile(string fileName);
	~Map();
};

