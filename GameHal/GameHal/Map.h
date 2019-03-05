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
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	~Map();
	friend ostream& operator<<(ostream& sout, Map m)
	{
		for (int i = 0; i < m.getWidth(); i++)
		{
			sout << '_';
		}
		sout << endl;
		for (int i = 0; i < m.getHeight(); i++)
		{
			for (int j = 0; j < m.getWidh(); j++)
			{
				if (m.map[i][j].getPassCost() == 1)
				{
					sout << ' ';
				}
				else if (m.map[i][j].getPassCost() == 0)
				{
					sout << "#";
				}
				else
				{
					sout << m.map[i][j].getPassCost();
				}
			}
			sout << '|' << endl;
		}
		for (int i = 0; i < m.getWidth(); i++)
		{
			sout << '-';
		}
		sout << endl;
		return sout;
	}
};

