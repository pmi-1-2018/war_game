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
void GameManager::Draw(const char& turn, int x, int y)const
{
	this->map->mapDraw(*map, x, y);
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
	string battleLog;
	char action;
	if (battleField->getIsBotArmy())
	{
		bool playerWon;
		cout << "Press \'a\' for auto fight, or any other key to fight manually";
		action = _getch();
		if (action == 'A' || action == 'a')
		{
			playerWon = players[0].armyAutoAttack(players[1]);
		}
		else
		{
			playerWon = players[0].battlePVE(players[1]);
		}
		if (!playerWon)
		{
			battleLog = this->turn + " lost.";
			return battleLog;
		}
	}
	else
	{
		bool playerWon;
		playerWon = players[0].battlePVP(players[1]);
		if (playerWon)
		{
			battleLog = this->turn + " won.";
			return battleLog;
		}
		else
		{
			battleLog = this->turn + " lost.";
			return battleLog;
		}
	}
	battleField->setIsPlayer(true);
	battleField->setIsBotArmy(false);
	battleField->SetArmy(&players[0]);
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
		PlaySound(TEXT("Utils\\menu_soundtrack.wav"), NULL, SND_ASYNC | SND_LOOP);
		return;
	}
	if (filename == "battle")
	{
		PlaySound(TEXT("Utils\\battle_soundtrack.wav"), NULL, SND_ASYNC | SND_LOOP);
		return;
	}
	if (filename == "Attack")//attack music
	{
		PlaySound(TEXT("Utils\\Combat01.wav"), NULL, SND_ASYNC | SND_LOOP);
		return;
	}
}

void GameManager::Start()
{
	if (this->mapGenerated == false)
	{
		GenerateMap(10, 10);
	}

	this->map->resetPlayers(this->turn);

	this->mapHeight = this->map->getHeight();
	this->mapWidth = this->map->getWidth();
	// mapheight - y, mapwidth - x
	
	SetMusic("battle");
	int x_1 = 1;
	int y_1 = 0;
	int x_2 = mapWidth-2;
	int y_2 = mapHeight-1;
	Draw(this->turn, x_1, y_1);
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
		// response = 3 - out of points - switching the turn
		if (hitTheWall == true) 
		{
			continue;
		}
		if (response == 0)
		{
			new_x = prev_x;
			new_y = prev_y;
			continue;
		}
		else if (response == 2)
		{
			string battleLog = StartBattle(new_x, new_y);
			int temp;
			Army* army = (this->map->GetCell(new_x, new_y))->GetArmy(temp);
			if (battleLog != "")
			{

				FileLogW(battleLog);
				bool cntinue = RestartGame();
				if (cntinue == false)
				{
					return;
				}
				break;
			}
			system("cls");
			this->map->SetBackground("I");
			cout << "Turn: " << this->turn << endl;
			cout << "Points left: " << army->GetCurrEnergy() << endl;
			Draw(this->turn, new_x, new_y);
			continue;
		}
		if (hitTheWall == false && response == 1 || response == 3)
		{
			outputTurnSwitch(response);
			system("CLS");
			int playersCount;
			Army* army = nullptr;
			if (response == 3)
			{
				army = currentCell->GetArmy(playersCount);
				SwitchTurn();
				new_x = prev_x;
				new_y = prev_y;
			}
			else
			{
				army = newCell->GetArmy(playersCount);
			}
			this->map->SetBackground("I");
			cout << "Turn: " << this->turn << endl;
			cout << "Points left: " << army->GetCurrEnergy() << endl;
			this->map->SetBackground("D");
			army = nullptr;
			if (response == 3)
			{
				if (new_x == x_1 && new_y == y_1)
				{
					Draw(this->turn, x_2, y_2);
				}
				else
				{
					Draw(this->turn, x_1, y_1);
				}
				continue;
			}
			Draw(this->turn, new_x, new_y);
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
		system("CLS");
		Start();
		break;
	case 110:
		return false;
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

void GameManager::outputTurnSwitch(int response)
{
	char key;
	int asciiValue;
	if (response == 3)
	{
		cout << "Press enter to end your turn" << endl;
		bool loop = true;
		while (loop)
		{
			key = _getch();
			asciiValue = key;
			if (asciiValue == 13)
			{
				system("CLS");
				asciiValue = 0;
				loop = false;
			}
		}
		cout << "Press enter to start your turn" << endl;
		loop = true;
		while (loop)
		{
			key = _getch();
			asciiValue = key;
			if (asciiValue == 13)
			{
				system("CLS");
				asciiValue = 0;
				loop = false;
			}
		}
	}
}
