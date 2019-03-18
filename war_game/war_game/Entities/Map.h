#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include"cell.h"
#include "Windows.h"
//#define DEBUG

using namespace std;

class Map
{
	
private:
	int width;
	int height;
	const HANDLE HSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	Cell **map;
public:
	Map();
	void readMapFromFile(string fileName);
	void generateRandomMap(string fileName, int height, int width);
	int getWidth();
	int getHeight();
	void SetBackground(const string flag)const;
	void setWidth(int width);
	void setHeight(int height);
	bool setPlayer(char symb, int x, int y);
	bool getIspassable(int a, int b);
	~Map();
	friend ostream& operator<<(ostream& sout, Map &m);
};

