#include "GameManager.h"


GameManager::GameManager() 
{
}
void GameManager::GenerateMap(int height, int width)
{
	this->mapHeight = height;
	this->mapWidth = width;
	map = new Map();
	map->generateRandomMap(this->MAP_PATH, this->mapHeight, this->mapWidth);
	this->mapGenerated = true;
	#ifdef DEBUG
	cout << "Notice! Map was generated. Now you can start playing." << endl;
		for (int i = 0; i < map->getHeight(); i++)
		{
			for (int j = 0; j < map->getWidth(); j++)
			{
				if (map->getIspassable(i, j) == false)
				{
					cout << i << " " << j << endl;
				}
			}
		}
	#endif
}
void GameManager::Draw()const
{
	cout << *(this->map);
	
}
void GameManager::SwitchTurn()
{
	if (this->turn == 'l')
	{
		this->turn = 'r';
	}
	else
	{
		this->turn = 'l';
	}
}

string GameManager::GetLogPath() const
{
	return this->LOG_PATH;
}

string GameManager::GetMapPath() const
{
	return this->MAP_PATH;
}



string GameManager::StartBattle(const int& x, const int& y) 
{
	SetMusic("Attack");
	cout << "Battle has started" << endl;
	Cell* battleField = this->map->GetCell(x, y);
	// battleField - cell with the array of two players
	int playersCount;
	Army* players = battleField->GetArmy(playersCount);
	// getting the players
	system("CLS");
	// test whether we got all players
	this->map->SetBackground("I");
	cout << players[0].GetSymb() << " " << players[1].GetSymb() << endl;
	this->map->SetBackground("D");



	string battleLog = "Someone has won";
	return battleLog;
}

bool GameManager::MapIsGenerated() const
{
	return this->mapGenerated;
}
int GameManager::MoveChar(char symb, Cell* prevCell, Cell* newCell)
{
	#ifdef DEBUG
		cout << "Moved " << symb << " to " << x << " " << y << endl;
	#endif
	int response = map->setPlayer(symb, prevCell, newCell);
	return response;
	
}

void GameManager::SetMusic(const string & filename)
{
	if (filename == "menu") 
	{
		PlaySound(TEXT("Utils\\menu_soundtrack.wav"), NULL, SND_ASYNC);
		return;
	}
	if (filename == "battle")
	{
		PlaySound(TEXT("Utils\\battle_soundtrack.wav"), NULL, SND_ASYNC);
		return;
	}
	if (filename == "Attack")//attack music
	{
		PlaySound(TEXT("Utils\\Combat01.wav"), NULL, SND_ASYNC);
		return;
	}
}

void GameManager::Start()
{
	if (this->mapGenerated == false)
	{
		GenerateMap(10, 10);
	}

	this->map->resetPlayers();

	this->mapHeight = this->map->getHeight();
	this->mapWidth = this->map->getWidth();
	// mapheight - y, mapwidth - x
	this->map->SetBackground("I");
	this->turn = 'l';
	cout << "Turn: " << this->turn << endl;
	this->map->SetBackground("D");
	Draw();
	SetMusic("battle");
	int x_1 = 1;
	int y_1 = 0;
	int x_2 = mapWidth-2;
	int y_2 = mapHeight-1;
	while (true)
	{
		int prev_x = turn == 'l' ? x_1 : x_2;
		int prev_y = turn == 'l' ? y_1 : y_2;
		bool hitTheWall = false;
		char key;
		int asciiValue;
		key = _getch();
		asciiValue = key;
		if (asciiValue == 97)
		{
			if (turn == 'l') {
				if (x_1 != 0) {
					x_1 -= 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
			else
			{
				if (x_2 != 0) {
					x_2 -= 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
		}
		else if (asciiValue == 100)
		{
			if (turn == 'l') {
				if (x_1 != mapWidth - 1) {
					x_1 += 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
			else
			{
				if (x_2 != mapWidth - 1) {
					x_2 += 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
		}
		else if (asciiValue == 119)
		{
			if (turn == 'l') {
				if (y_1 != 0) {
					y_1 -= 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
			else
			{
				if (y_2 != 0) {
					y_2 -= 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
		}
		else if (asciiValue == 115)
		{
			if (turn == 'l') {
				if (y_1 != mapHeight - 1) {
					y_1 += 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
			else
			{
				if (y_2 != mapHeight - 1) {
					y_2 += 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
		}
		else if (asciiValue == 27)
		{
			break;
		}
		char symb = turn == 'l' ? 'F' : 'S';
		int& new_x = turn == 'l' ? x_1 : x_2;
		int& new_y = turn == 'l' ? y_1 : y_2;
		Cell* currentCell = this->map->GetCell(prev_x, prev_y);
		Cell* newCell = this->map->GetCell(new_x, new_y);
		int response = MoveChar(symb, currentCell, newCell);
		// response = 0 - hit the obstacle
		// response = 1 - moved successfully
		// response = 2 - hit the player, begining of the battle

		if (response == 0)
		{
			new_x = prev_x;
			new_y = prev_y;
			continue;
		}
		else if (response == 2)
		{
			string battleLog = StartBattle(new_x, new_y);
			FileLogW(battleLog);
			bool cntinue = RestartGame();
			if (cntinue == false) 
			{
				return;
			}
			break;
		}
		if (hitTheWall == false && response == 1)
		{
			system("CLS");
			SwitchTurn();
			this->map->SetBackground("I");
			cout << "Turn: " << this->turn << endl;
			this->map->SetBackground("D");
			Draw();
		}
	}
}
void GameManager::FileLogW(string information)
{
	ofstream ofs(this->LOG_PATH);
	bool checker = ofs.is_open();
	if (checker == true) 
	{
		ofs << information;
	}
	else 
	{
		this->map->SetBackground("");
		cout << "Error while writing the file" << endl;
	}
	ofs.close();
}

void GameManager::SetBackground(string flag)
{
	Map temp;
	temp.SetBackground(flag);
}

bool GameManager::RestartGame()
{
	this->map->SetBackground("");
	cout << "Do you want to play once more? - y/n";
	char key = _getch();
	int asciiVal = key;
	switch (asciiVal)
	{
	case 121:
	{
		system("CLS");

		Start();
		break;
	}
	case 110:
	{
		return false;
	}
	}
}

void GameManager::MapFileSet()
{
	this->map->readMapFromFile(this->MAP_PATH);
}

GameManager::~GameManager()
{
	delete map;
}
