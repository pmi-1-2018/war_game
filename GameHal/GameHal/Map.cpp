#include "Map.h"

Map::Map() :
	width(0),
	height(0)
{}



void Map::readMapFromFile(string fileName)
{
	int modelHeight;//читання карти з файлу
	int modelWidth;
	ifstream myfile;
	myfile.open(fileName);
	myfile >> modelHeight >> modelWidth;
	char **matrix = new char*[modelHeight];
	for (int i = 0; i < modelHeight; i++)
	{
		matrix[i] = new char[modelWidth];
		for (int j = 0; j < modelWidth; j++)
		{
			myfile >> matrix[i][j];
		}
	}
	myfile.close();
	if (this->height == 0 && this->width == 0)
	{ 
		this->height = modelHeight;
		this->width = modelWidth;
		map = new Cell*[height];
		for (int i = 0; i < height; i++)
		{
			map[i] = new Cell[width];
			for (int j = 0; j < width; j++)
			{
				map[i][j].setCell(matrix[i][j]);
			}
		}
	}
	if (this->height == modelHeight && this->width == modelWidth)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				map[i][j].setCell(matrix[i][j]);
			}
		}
	}
	if (this->height != modelHeight || this->width != modelWidth)
	{
		this->~Map();
		this->height = modelHeight;
		this->width = modelWidth;
		map = new Cell*[height];
		for (int i = 0; i < height; i++)
		{
			map[i] = new Cell[width];
			for (int j = 0; j < width; j++)
			{
				map[i][j].setCell(matrix[i][j]);
			}
		}
	}
}

void Map::generateRandomMap(string fileName, int height, int width)
{
	this->height = height;
	this->width = width;
	map = new Cell*[height];
	for (int i = 0; i < height; i++)
	{
		map[i] = new Cell[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = Cell(rand()% 4, rand() % 8);
		}
	}
	this->printMapIntoFile(fileName);
}

void Map::printMapIntoFile(string fileName)
{	
	ofstream myfile;
	myfile.open(fileName);
	myfile << height << " " << width << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			switch (map[i][j].getPassCost())
			{
			case 0:
				myfile << '#';
				break;
			case 1:
				myfile << '1';
				break;
			case 2:
				myfile << '2';
				break;
			case 3:
				myfile << '3';
				break;
			default:
				myfile << '1';
				break;
			}
		}
		myfile << endl;
	}
	myfile.close();
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}
