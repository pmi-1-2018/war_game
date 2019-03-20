#include "Map.h"

Map::Map() :
	width(0),
	height(0)
{}

void Map::SetBackground(const string flag) const
{
	// D - default
	// 1 - first player
	// 2 - second player
	// O - obstacle
	// I - information
	if (flag == "D") {
		SetConsoleTextAttribute(this->HSTDOUT,
			BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
		return;
	}
	else if (flag == "O")
	{
		SetConsoleTextAttribute(this->HSTDOUT,
			BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_RED);
		return;
	}
	else if (flag == "1")
	{
		SetConsoleTextAttribute(this->HSTDOUT,
			BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
		return;
	}
	else if (flag == "2")
	{
		SetConsoleTextAttribute(this->HSTDOUT,
			BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE);
		return;
	}
	else if (flag == "I")
	{
		SetConsoleTextAttribute(this->HSTDOUT, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return;
	}
	else 
	{
		SetConsoleTextAttribute(this->HSTDOUT, 7);
	}
}

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


int Map::setPlayer(char symb, int x, int y)
{
	if (map[y][x].IsPassable() == true) {
		bool removePrev = false;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (map[i][j].IsPlayer() == true && map[i][j].GetArmySign() == symb)
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
		if (map[y][x].getIsPlayer() == true && map[y][x].GetArmySign() != NULL)
		{
			return 2;
		}
		else
		{
			map[y][x].SetPlayer(true, symb);
		}
		return 1;
	}
	else 
	{
		return 0;
	}
}

bool Map::getIspassable(int a, int b)
{
	return this->map[a][b].IsPassable();
}

void Map::resetPlayers()
{
	// cleaning the map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (map[i][j].IsPlayer() == true)
			{
				map[i][j].SetPlayer(false, NULL);
			}
		}
	}
	// setting the default position of the players.
	map[0][1] = Cell(1, 0, 0);
	map[0][1].SetPlayer(true, 'F');
	map[this->height - 1][this->width - 2] = Cell(1, this->width - 1, this->height - 1);
	map[this->height - 1][this->width - 2].SetPlayer(true, 'S');
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
				string flag = to_string(m.map[i][j].GetArmyId());
				m.SetBackground(flag);
				sout << m.map[i][j].GetArmySign();
				m.SetBackground("D");
				continue;
			}
			if (m.map[i][j].getPassCost() == 1)
			{
				m.SetBackground("D");
				sout << ' ';
			}
			else if (m.map[i][j].IsPassable() == false)
			{
				m.SetBackground("O");
				sout << '#';
				m.SetBackground("D");
			}
			else
			{
				sout << m.map[i][j].getPassCost();
			}
		}
		sout << '|' << endl;
	}
	for (int i = 0; i <= m.getWidth(); i++)
	{
		sout << '-';
	}
	SetConsoleTextAttribute(m.HSTDOUT, 0);
	sout << endl;
	return sout;
}
