#include "Map.h"

Map::Map() :
	width(0),
	height(0)
{}


void Map::readMapFromFile(string fileName)
{
	int modelHeight;
	int modelWidth;
	ifstream myfile;
	myfile.open(fileName);
	myfile >> modelHeight >> modelWidth;
	char **matrix = new char*[modelHeight];
	string getStr;
	getline(myfile, getStr);
	for (int i = 0; i < modelHeight; i++)
	{
		matrix[i] = new char[modelWidth];
		getline(myfile, getStr);
		for (int j = 0; j < modelWidth; j++)
		{
			matrix[i][j] = getStr[j];
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
	if (this->height != 0 || this->width != 0)
	{
		this->~Map();
	}
	this->height = height;
	this->width = width;
	map = new Cell*[height];
	for (int i = 0; i < height; i++)
	{
		map[i] = new Cell[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = Cell(rand()% 4, j, i);
		}
	}
	map[0][0] = Cell(1, 0, 0);
	map[0][0].SetPlayer(true, '*');
	map[this->height-1][this->width-1] = Cell(1, this->width - 1, this->height - 1);
	map[this->height - 1][this->width - 1].SetPlayer(true, '$');
	ofstream myfile;
	myfile.open(fileName);
	bool check = myfile.is_open();
	if (check) {
		myfile << height << " " << width << endl << *this;
	}
	myfile.close();
}
int Map::getHeight()
{
	return height;
}

int Map::getWidth()
{
	return width;
}

void Map::setHeight(int h)
{
	height = h;
}

bool Map::setPlayer(char symb, int x, int y)
{
	if (map[y][x].IsPassable() == true) {
	bool removePrev = false;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (map[i][j].IsPlayer() == true && map[i][j].GetArmy() == symb) 
			{
				map[i][j].SetPlayer(false, NULL);
				removePrev = true;
				break;
			}
		}
		if (removePrev)
		{
			break;
		}
	}
	
		map[y][x].SetPlayer(true, symb);
		return true;
	}
	else 
	{
		return false;
	}
}

bool Map::getIspassable(int a, int b)
{
	return this->map[a][b].IsPassable();
}

void Map::setWidth(int w)
{
	width = w;
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

ostream& operator<<(ostream& sout, Map &m)
{
	for (int i = 0; i < m.getHeight(); i++)
	{
		for (int j = 0; j < m.getWidth(); j++)
		{
			if (m.map[i][j].IsPlayer() == true)
			{
				sout << m.map[i][j].GetArmy();
				continue;
			}
			if (m.map[i][j].getPassCost() == 1)
			{
				sout << ' ';
			}
			else if (m.map[i][j].IsPassable() == false)
			{
				sout << '#';
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