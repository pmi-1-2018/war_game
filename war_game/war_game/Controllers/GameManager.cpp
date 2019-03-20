#include "GameManager.h"


GameManager::GameManager() 
{
}
void GameManager::GenerateMap(int height, int width)
{
	this->mapHeight = height;
	this->mapWidth = width;
	map = new Map();
	map->generateRandomMap(this->MAP_PATH, mapHeight, mapWidth);
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



string GameManager::StartBattle() const
{
	system("CLS");
	this->map->SetBackground("I");
	cout << "Battle has started" << endl;
	this->map->SetBackground("D");

	string battleLog = "Someone has won";
	return battleLog;
}

bool GameManager::MapIsGenerated() const
{
	return this->mapGenerated;
}
int GameManager::MoveChar(char symb, int x, int y) 
{
	#ifdef DEBUG
		cout << "Moved " << symb << " to " << x << " " << y << endl;
	#endif
	int response = map->setPlayer(symb, x, y);
	return response;
	
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
				if (x_1 != mapHeight - 1) {
					x_1 += 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
			else
			{
				if (x_2 != mapHeight - 1) {
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
				if (y_1 != mapWidth - 1) {
					y_1 += 1;
				}
				else
				{
					hitTheWall = true;
				}
			}
			else
			{
				if (y_2 != mapWidth - 1) {
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

		int response = MoveChar(symb, new_x, new_y);
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
			string battleLog = StartBattle();
			FileLogW(battleLog);
			RestartGame();
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

void GameManager::RestartGame()
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
		break;
	}
	}
}

GameManager::~GameManager()
{
	delete map;
}
