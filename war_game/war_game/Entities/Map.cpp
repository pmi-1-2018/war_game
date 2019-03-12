#include "Map.h"

Map::Map() :
	width(0),
	height(0)
{}


<<<<<<< HEAD
void Map::readMapFromFile(string fileName)
{
	int modelHeight;//������� ����� � �����
=======

void Map::readMapFromFile(string fileName)
{
	int modelHeight;
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
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
<<<<<<< HEAD
	map[0][0].setCell('*');
	map[49][49].setCell('$');

=======
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
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
<<<<<<< HEAD
			map[i][j] = Cell(rand()% 4, rand() % 8, i, j);
=======
			map[i][j] = Cell(rand()% 4);
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
		}
	}
	ofstream myfile;
	myfile.open(fileName);
<<<<<<< HEAD
	bool check = myfile.is_open();
=======
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
	myfile << height << " " << width << endl << *this;
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

void Map::setWidth(int w)
{
	width = w;
}

<<<<<<< HEAD
=======
bool Map::getIspassable(int a, int b)
{
	return this->map[a][b].getIsPassable();
}

>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
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
			if (m.map[i][j].getPassCost() == 1)
			{
				sout << ' ';
			}
<<<<<<< HEAD
			else if (m.map[i][j].getPassCost() == 0)
			{
				sout << "#";
=======
			else if (m.map[i][j].getIsPassable() == false)
			{
				sout << '#';
>>>>>>> fcbf33cd102aa010fa648d5a6aba6668a27c803a
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