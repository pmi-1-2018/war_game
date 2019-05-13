#include "GameManager.h"


GameManager::GameManager()
{
	font.loadFromFile("Utils/arial.ttf");
	backgroundTexture.loadFromFile("Utils/backgroundImage.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(sf::Vector2f(1.25f, 1.f));
}
sf::Font& GameManager::getFont()
{
	return this->font;
}
sf::Sprite& GameManager::getBackgroundSprite()
{
	return this->backgroundSprite;
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
	if (this->turn == 'F')
	{
		this->turn = 'S';
	}
	else
	{
		this->turn = 'F';
	}
	this->numberOfTurn++;
}

string GameManager::GetLogPath() const
{
	return this->LOG_PATH;
}

string GameManager::GetMapPath() const
{
	return this->MAP_PATH;
}

string GameManager::StartBattle(Army* a1, Army* a2)
{
	if (a1 == nullptr || a2 == nullptr)
	{
		throw "Nullptr came to the func";
	}
	SetMusic("Attack");
	cout << "Battle has started" << endl;
	//Cell* battleField = this->map->GetCell(x, y);
	// battleField - cell with the array of two players
	//int playersCount;
	//Army* players = battleField->GetArmy(playersCount);
	// getting the players
	system("CLS");
	// test whether we got all players
	string battleLog;
	char action;
	if (a2->getIsBotArmy() == true)
	{
		bool playerWon;
		cout << "Press \'a\' for auto fight, or any other key to fight manually";
		action = _getch();
		if (action == 'A' || action == 'a')
		{
			playerWon = a1->armyAutoAttack(*a2);
		}
		else
		{
			playerWon = a1->battlePVE(*a2);
		}
		if (!playerWon)
		{
			battleLog = this->turn + "lost.";
			return battleLog;
		}
	}
	else
	{
		bool playerWon;
		playerWon = a1->battlePVP(*a2);
		if (playerWon)
		{
			battleLog = this->turn + "won.";
			return battleLog;
		}
		else
		{
			battleLog = this->turn + "lost.";
			return battleLog;
		}
	}
	/*battleField->setIsPlayer(true);
	battleField->setIsBotArmy(false);
	battleField->SetArmy(&players[0]);*/
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

void GameManager::DrawMap(sf::Sprite& mapSprite, sf::RenderWindow& App)
{
	this->map->DrawMapIntoWindow(mapSprite, App);
}

void GameManager::outputInfoOverMap(Army* army)
{
	this->map->SetBackground("I");
	cout << "Turn: " << this->turn << endl;
	cout << "Points left: " << army->GetCurrEnergy() << endl;
	cout << "Money: " << army->getWallet() << " rupees." << endl;
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
	int x_2 = mapWidth - 2;
	int y_2 = mapHeight - 1;
	Draw(this->turn, x_1, y_1);

	while (true)
	{
		int prev_x = turn == 'F' ? x_1 : x_2;
		int prev_y = turn == 'F' ? y_1 : y_2;
		bool hitTheWall = false;
		char key;
		int asciiValue;
		key = _getch();
		asciiValue = key;
		if (asciiValue == 97)
		{
			if (turn == 'F') {
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
			if (turn == 'F') {
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
			if (turn == 'F') {
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
			if (turn == 'F') {
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
		char symb = turn == 'F' ? 'F' : 'S';
		int& new_x = turn == 'F' ? x_1 : x_2;
		int& new_y = turn == 'F' ? y_1 : y_2;
		Cell* currentCell = this->map->GetCell(prev_x, prev_y);
		Cell* newCell = this->map->GetCell(new_x, new_y);
		int response = MoveChar(symb, currentCell, newCell);
		if (hitTheWall == true)
		{
			continue;
		}
		if (response == hitObstacle)
		{
			new_x = prev_x;
			new_y = prev_y;
			continue;
		}
		else if (response == hitPlayer)
		{
			Army* a1 = currentCell->getArmyPtr();
			Army* a2 = newCell->getArmyPtr();
			string battleLog = StartBattle(a1, a2);
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
			Army* army = (this->map->GetCell(prev_x, prev_y))->GetArmy();
			currentCell->setIsPlayer(false);
			currentCell->SetArmy(nullptr);
			newCell->SetArmy(army);
			newCell->setIsPlayer(true);
			newCell->setIsBotArmy(false);
			SetMusic("battle");
			army->SetCurrEnergy(-army->GetCurrEnergy());
			outputInfoOverMap(army);
			Draw(this->turn, new_x, new_y);
			continue;
		}
		if (response == enteredBarrack)
		{
			system("CLS");
			while (this->map->GetCell(new_x, new_y)->getBarrackPtr()->GetNumberOfTurn() - numberOfTurn >= 7)
			{
				this->map->GetCell(new_x, new_y)->getBarrackPtr()->SetNumberOfUnits(
					this->map->GetCell(new_x, new_y)->getBarrackPtr()->GetNumberOfUnits() + 5);
				this->map->GetCell(new_x, new_y)->getBarrackPtr()->SetNumberOfTurn(
					this->map->GetCell(new_x, new_y)->getBarrackPtr()->GetNumberOfTurn() + 7);
			}
			Army* army = newCell->GetArmy();			
			int n;
			Barrack *barrack = this->map->GetCell(new_x, new_y)->getBarrackPtr();
			bool check = true;
			while (check)
			{
				system("CLS");
				cout << "Welcome to the " << barrack->TellType() << endl;
				cout << "Enter what you want to do: " << endl;
				cout << "1 - take units" << endl;
				cout << "2 - swap units" << endl;
				cout << "3 - exit" << endl;
				cin >> n;
				if (n == 1)
				{
					cout << "How many units you want to take? " << endl;
					int number;
					cin >> number;
					while (army->getNumberOfUnits() != army->GetCapacity() && barrack->GetNumberOfUnits() != 0 && number != 0)
					{
						army->addUnit(barrack->giveUnit());
						barrack->SetNumberOfUnits(barrack->GetNumberOfUnits() - 1);
						number--;
					}
				}
				if (n == 3)
				{
					check = false;
				}
				if (n == 2)
				{
					int index1;
					int index2;
					army->swapUnits(index1,index2);
					army->ArmySwap(index1, index2);
				}
			}
			system("CLS");
			outputInfoOverMap(army);
			Draw(this->turn, new_x, new_y);
			continue;
		}
		if (response == enteredGoldMine)
		{
			Army *army = newCell->GetArmy();
			GoldMine *goldMine = newCell->getGoldMinePtr();
			if (goldMine->getOwner() == 'N')
			{
				goldMine->setOwner(this->turn);
				goldMine->setPointerToOwner(army);
				army->increaseIncome(goldMine->getIncome());
			}
			else if (goldMine->getOwner() == this->turn)
			{

			}
			else
			{
				goldMine->getPointerToOwner()->increaseIncome(-(goldMine->getIncome()));
				goldMine->setOwner(this->turn);
				goldMine->setPointerToOwner(army);
				army->increaseIncome(goldMine->getIncome());
			}
			system("CLS");
			outputInfoOverMap(army);
			Draw(this->turn, new_x, new_y);
			continue;
		}
		if (hitTheWall == false && response == movedSuccessfully || response == outOfPoints)
		{
			outputTurnSwitch(response);
			system("CLS");
			Army* army = nullptr;
			if (response == outOfPoints)
			{
				SwitchTurn();
				new_x = prev_x;
				new_y = prev_y;
				if (new_x == x_1 && new_y == y_1)
				{
					army = this->map->GetCell(x_2, y_2)->GetArmy();
				}
				else
				{
					army = this->map->GetCell(x_1, y_1)->GetArmy();
				}
				army->addMoneyToWallet(army->getIncome());
			}
			else
			{
				army = newCell->GetArmy();
			}
			outputInfoOverMap(army);
			this->map->SetBackground("D");
			army = nullptr;
			if (response == outOfPoints)
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
	if (response == outOfPoints)
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
