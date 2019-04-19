#include "Map.h"

Map::Map() :
	width(0),
	height(0)
{}
void printMap(Cell **map, int height, int width) {
	cout << "#####################" << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << map[i][j];
		}
		cout << endl;

	}
	cout << "#####################" << endl;
}
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
				map[i][j].setCell(matrix[i][j], j, i);
			}
		}
	}
	if (this->height == modelHeight && this->width == modelWidth)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				map[i][j].setCell(matrix[i][j], j, i);
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
				map[i][j].setCell(matrix[i][j], j, i);
			}
		}
	}
}

void Map::generateRandomMap(string fileName, int height, int width)
{
	srand(time(NULL));
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
	}

	int countOfCells = this->height * this->width;

	//countofbarriers will be generated from 10% to 25%
	int countOfBarriers = 0;
	do
	{
		countOfBarriers = (rand() % countOfCells);
	} while (countOfBarriers > (countOfCells / 4) || countOfBarriers < (countOfCells / 10));

	//count of lonely barriers
	int countOfLonelyBarriers = countOfBarriers / 4;

	Cell* lonelyBarriers = new Cell[countOfLonelyBarriers];

	int i = 0;
	while (i < countOfLonelyBarriers)
	{
		int x = rand() % this->width;
		int y = rand() % this->height;
		if (map[y][x].IsPassable())
		{
			map[y][x].setCell('#', x, y);
			lonelyBarriers[i] = map[y][x];
			i++;
		}
	}


	bool* isLonely = new bool[countOfLonelyBarriers];
	for (int i = 0; i < countOfLonelyBarriers; i++)
	{
		isLonely[i] = true;
	}
	for (int i = 0; i < countOfLonelyBarriers; i++)
	{
		while (isLonely[i])
		{
			int shape = rand() % 6;
			switch (shape)
			{
			case 0:
			{
				if (lonelyBarriers[i].GetX() + 1 < this->width && lonelyBarriers[i].GetY() + 2 < this->height)
				{
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() + 1].setCell('#', lonelyBarriers[i].GetX() + 1, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY() + 1][lonelyBarriers[i].GetX() + 1].setCell('#', lonelyBarriers[i].GetX() + 1, lonelyBarriers[i].GetY() + 1);
					map[lonelyBarriers[i].GetY() + 2][lonelyBarriers[i].GetX() + 1].setCell('#', lonelyBarriers[i].GetX() + 1, lonelyBarriers[i].GetY() + 2);
					isLonely[i] = false;
				}
				break;
			}
			case 1:
			{
				if (lonelyBarriers[i].GetX() + 2 < this->width && lonelyBarriers[i].GetY() + 1 < this->height)
				{
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() + 1].setCell('#', lonelyBarriers[i].GetX() + 1, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() + 2].setCell('#', lonelyBarriers[i].GetX() + 2, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY() + 1][lonelyBarriers[i].GetX() + 2].setCell('#', lonelyBarriers[i].GetX() + 2, lonelyBarriers[i].GetY() + 1);
					isLonely[i] = false;
				}
				break;
			}
			case 2:
			{
				if (lonelyBarriers[i].GetX() - 2 >= 0 && lonelyBarriers[i].GetY() - 1 >= 0)
				{
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() - 1].setCell('#', lonelyBarriers[i].GetX() - 1, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() - 2].setCell('#', lonelyBarriers[i].GetX() - 2, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY() - 1][lonelyBarriers[i].GetX() - 2].setCell('#', lonelyBarriers[i].GetX() - 2, lonelyBarriers[i].GetY() - 1);
					isLonely[i] = false;
				}
				break;
			}
			case 3:
			{
				if (lonelyBarriers[i].GetX() - 2 >= 0 && lonelyBarriers[i].GetY() + 1 < this->height)
				{
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() - 1].setCell('#', lonelyBarriers[i].GetX() - 1, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() - 2].setCell('#', lonelyBarriers[i].GetX() - 2, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY() + 1][lonelyBarriers[i].GetX() - 2].setCell('#', lonelyBarriers[i].GetX() - 2, lonelyBarriers[i].GetY() + 1);
					isLonely[i] = false;
				}
				break;
			}
			case 4:
			{
				if (lonelyBarriers[i].GetX() + 2 < this->width && lonelyBarriers[i].GetY() - 1 >= 0)
				{
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() + 1].setCell('#', lonelyBarriers[i].GetX() + 1, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() + 2].setCell('#', lonelyBarriers[i].GetX() + 2, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY() - 1][lonelyBarriers[i].GetX() + 2].setCell('#', lonelyBarriers[i].GetX() + 2, lonelyBarriers[i].GetY() - 1);
					isLonely[i] = false;
				}
				break;
			}
			case 5:
			{
				if (lonelyBarriers[i].GetX() - 1 >= 0 && lonelyBarriers[i].GetY() + 2 < this->height)
				{
					map[lonelyBarriers[i].GetY()][lonelyBarriers[i].GetX() - 1].setCell('#', lonelyBarriers[i].GetX() - 1, lonelyBarriers[i].GetY());
					map[lonelyBarriers[i].GetY() + 1][lonelyBarriers[i].GetX() - 1].setCell('#', lonelyBarriers[i].GetX() - 1, lonelyBarriers[i].GetY() + 1);
					map[lonelyBarriers[i].GetY() + 2][lonelyBarriers[i].GetX() - 1].setCell('#', lonelyBarriers[i].GetX() - 1, lonelyBarriers[i].GetY() + 2);
					isLonely[i] = false;
				}
				break;
			}

			default:
				break;
			}
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j].IsPassable())
			{
				map[i][j] = Cell((rand() % 3) + 1, j, i);
			}
		}
	}
	int maxGoldMinesQuantity = this->height * this->width / 50;
	for (size_t i = 0; i < maxGoldMinesQuantity; i++)
	{
		int x = rand() % width;
		int y = rand() % height;
		if ((x == 1 && y == 0) || (x == width - 2 && y == height - 1) || !map[y][x].isPossibleGenerate())
		{
			i--;
			continue;
		}
		map[y][x].setCell('G', x, y);
	}
	int maxBarracksQuantity = this->height * this->width / 50;
	for (int i = 0; i < maxBarracksQuantity; i++)
	{
		int x = rand() % width;
		int y = rand() % height;
		if ((x == 1 && y == 0) || (x == width - 2 && y == height - 1) || !map[y][x].isPossibleGenerate())
		{
			i--;
			continue;
		}
		map[y][x].setCell('B', x, y);
	}
	int maxBotArmiesQuantity = this->height * this->width / 50;
	for (int i = 0; i < maxBotArmiesQuantity; i++)
	{
		int x = rand() % width;
		int y = rand() % height;
		if ((x == 1 && y == 0) || (x == width - 2 && y == height - 1) || !map[y][x].isPossibleGenerate())
		{
			i--;
			continue;
		}
		map[y][x].setCell('A', x, y);
	}
	ofstream myfile;
	myfile.open(fileName);
	bool check = myfile.is_open();
	if (check)
	{
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


int Map::setPlayer(char symb, Cell* prevCell, Cell* newCell)
{
	Army* army_1 = nullptr;
	if (newCell != nullptr && newCell->IsPassable() == true)
	{
		bool removePrev = false;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j].IsPlayer() == true && map[i][j].GetArmySign() == symb)
				{
					army_1 = map[i][j].GetArmy();
					map[i][j].SetPlayer(nullptr);
					removePrev = true;
					break;
				}
			}
			if (removePrev)
			{
				break;
			}
		}
		if ((map[newCell->GetY()][newCell->GetX()].getIsPlayer() == true || map[newCell->GetY()][newCell->GetX()].getIsBotArmy() == true) && map[newCell->GetY()][newCell->GetX()].GetArmySign() != NULL)
		{
			/*int playersCount;
			Army* army_2 = this->map[newCell->GetY()][newCell->GetX()].GetArmy(playersCount);
			Army* players = new Army[2];
			players[0] = *army_1;
			players[1] = *army_2;
			this->map[newCell->GetY()][newCell->GetX()].SetBattleField(players, 2);*/
			map[prevCell->GetY()][prevCell->GetX()].SetPlayer(army_1);
			return 2;
		}
		else if (map[newCell->GetY()][newCell->GetX()].IsBarrack() == true)
		{
			int cellWeight = newCell->getPassCost();
			bool noPoints = army_1->SetCurrEnergy(-cellWeight);
			map[prevCell->GetY()][prevCell->GetX()].SetArmy(nullptr);
			map[newCell->GetY()][newCell->GetX()].SetPlayer(army_1);
			prevCell = nullptr;
			return 4;
		}
		else
		{
			int cellWeight = newCell->getPassCost();
			bool noPoints = army_1->SetCurrEnergy(-cellWeight);
			map[prevCell->GetY()][prevCell->GetX()].SetArmy(nullptr);
			map[newCell->GetY()][newCell->GetX()].SetPlayer(army_1);
			if (noPoints == true)
			{
				map[newCell->GetY()][newCell->GetX()].SetPlayer(nullptr);
				map[prevCell->GetY()][prevCell->GetX()].SetPlayer(army_1);
				return 3;
			}
			return 1;
		}
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

void Map::resetPlayers(char& turn)
{
	// cleaning the map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j].IsPlayer() == true)
			{
				map[i][j].SetPlayer(nullptr);
			}
		}
	}
	// setting the default position of the players.
	Swordsman units[2];
	Army* player_1 = new Army("Aliance", units, 2, 'F', true);
	Army* player_2 = new Army("Horde", units, 2, 'S', true);
	// cin>>player_1,player_2
	map[0][1].SetPlayer(player_1);
	map[this->height - 1][this->width - 2].SetPlayer(player_2);

	SetBackground("I");
	turn = 'l';
	cout << "Turn: " << turn << endl;
	cout << "Points left: " << player_1->GetCurrEnergy() << endl;
	SetBackground("D");
}

Cell* Map::GetCell(const int& x, const int& y) const
{
	if (x < this->width && y < this->height) {
		return &(this->map[y][x]);
	}
	return nullptr;
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

void Map::mapDraw(Map &m, int x, int y)
{	
	for (int i = 0; i < m.getHeight(); i++)
	{
		for (int j = 0; j < m.getWidth(); j++)
		{
			if (abs(m.map[i][j].GetX() - x) + abs(m.map[i][j].GetY() - y) > 3)
			{
				SetConsoleTextAttribute(m.HSTDOUT, 64);
				
				cout << ' ';
				continue;
			}
			if (m.map[i][j].getIsPlayer() == true)
			{
				string flag = to_string(m.map[i][j].GetArmyId());
				m.SetBackground(flag);
				cout << m.map[i][j].GetArmySign();
				m.SetBackground("D");
				continue;
			}
			if (m.map[i][j].getBarrackPtr() != nullptr)
			{
				m.SetBackground("D");
				cout << 'B';
				continue;
			}
			if (m.map[i][j].getGoldMinePtr() != nullptr)
			{
				m.SetBackground("D");
				cout << 'G';
				continue;
			}
			if (m.map[i][j].getIsBotArmy() == true)
			{
				m.SetBackground("D");
				cout << 'A';
				continue;
			}
			if (m.map[i][j].getPassCost() == 1)
			{
				m.SetBackground("D");
				cout << ' ';
			}
			else if (m.map[i][j].IsPassable() == false)
			{
				m.SetBackground("O");
				cout << '#';
				m.SetBackground("D");
			}
			else
			{
				m.SetBackground("D");
				//cout << m.map[i][j].getPassCost();
				cout << '.';
			}
		}
		SetConsoleTextAttribute(m.HSTDOUT, 64);
		cout << '|' << endl;
	}
	SetConsoleTextAttribute(m.HSTDOUT, 64);
	for (int i = 0; i <= m.getWidth(); i++)
	{
		cout << '-';
	}
	SetConsoleTextAttribute(m.HSTDOUT,15);
	cout << endl;
}

ostream& operator<<(ostream& sout, Map &m)
{
	for (int i = 0; i < m.getHeight(); i++)
	{
		for (int j = 0; j < m.getWidth(); j++)
		{
			if (m.map[i][j].getIsPlayer() == true)
			{
				string flag = to_string(m.map[i][j].GetArmyId());
				m.SetBackground(flag);
				sout << m.map[i][j].GetArmySign();
				m.SetBackground("D");
				continue;
			}
			if (m.map[i][j].getBarrackPtr() != nullptr)
			{
				sout << 'B';
				continue;
			}
			if (m.map[i][j].getGoldMinePtr() != nullptr)
			{
				sout << 'G';
				continue;
			}
			if (m.map[i][j].getIsBotArmy() != false)
			{
				sout << 'A';
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
	SetConsoleTextAttribute(m.HSTDOUT, 15);
	sout << endl;
	return sout;
}
