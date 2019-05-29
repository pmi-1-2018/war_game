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
	int playersCount;
	system("CLS");
	string battleLog;
	string currentTurn;
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
			currentTurn = string(1, this->turn);
			battleLog = currentTurn + " lost.";
			cout << endl << battleLog << endl;
			return battleLog;
		}
	}
	else
	{
		bool playerWon;
		playerWon = a1->battlePVP(*a2);
		currentTurn = string(1, this->turn);
		battleLog = currentTurn == "S" ? currentTurn + " lost." : currentTurn + " won";
		cout << endl << battleLog << endl;
		return battleLog;
	}
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

void GameManager::outputInfoOverMap(Army* army)
{
	this->map->SetBackground("I");
	cout << "Turn: " << this->turn << endl;
	cout << "Points left: " << army->GetCurrEnergy() << endl;
	cout << "Money: " << army->getWallet() << " rupees." << endl;
}

void GameManager::SandboxStart()
{
	vector<Unit>ar1;
	vector<Unit>ar2;
	Army a1("dada",ar1,'s',1,100);
	Army a2("nene", ar2, 's', 1, 100);
	int size1 = -1;
	int size2 = -1;
	int var = 0;
	while (true)
	{
		while (size1 < 1 || size1 > 200)
		{
			cout << "Enter the size of the first army: " << endl;
			cin >> size1;
		}
		a1.inputTheArmy(size1);
		while (size2 < 0 || size2 > 200)
		{
			cout << "Enter the size of the second army: " << endl;
			cin >> size2;
		}
		a2.inputTheArmy(size2);
		a1.printArmiesFight(a1, true);

		SetMusic("Attack");
		a1.armyAutoAttack(a2);
		system("pause");
		break;
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
		if (asciiValue == 97) // pressed a
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
		else if (asciiValue == 100) // pressed d
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
		else if (asciiValue == 119) // pressed w
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
		else if (asciiValue == 115) // pressed s
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
		else if (asciiValue == 27)// pressed escape
		{
			break;
		}
		else if(asciiValue != 105)
		{
			continue;
		}
		char symb = turn == 'F' ? 'F' : 'S';
		int& new_x = turn == 'F' ? x_1 : x_2;
		int& new_y = turn == 'F' ? y_1 : y_2;
		Cell* currentCell = this->map->GetCell(prev_x, prev_y);
		if (asciiValue == 105) // pressed i (inventory)
		{
			currentCell->GetArmy()->InventoryMode();
			system("cls");
			outputInfoOverMap(currentCell->GetArmy());
			Draw(this->turn, prev_x, prev_y);
			continue;
		}
		Cell* newCell = this->map->GetCell(new_x, new_y);
		int response = MoveChar(symb, currentCell, newCell);
		// response = 0 - hit the obstacle
		// response = 1 - moved successfully
		// response = 2 - hit the player, begining of the battle
		// response = 3 - out of points - switching the turn
		// response = 4 - stepped on a barrack
		// response = 5 - stepped on a Gold Mine
		// response = 6 - stepped on a artifact
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
		if (response == 4)
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
		if (response == 5)
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
		if (response == 6)
		{
			system("CLS");
			Artifact* artifact = newCell->getArifactPtr();
			artifact->printArtifactInfo();
			cout << "Do you want to take this artifact? \n"
				 << "Press 'y' to pick up\n"
				 << "Press 'n' not to pick up\n"
				 << "Press 'd' to destroy\n";
			char answer = _getch();
			Army* army = nullptr;
			army = newCell->GetArmy();
			if (answer == 'y' || answer == 'Y')
			{
				bool artIsAdded = army->getInventory()->AddArtifact(artifact);
				newCell->setArtifactPtr(nullptr);
				system("CLS");
				if (artIsAdded == false)
				{
					cout << "Whoops.. Missing space!\nDelete any artifact and come back again!" << endl;
				}
				else
				{
					cout << "You successfully added new artifact to your inventory" << endl;
				}
			}
			else if (answer == 'd' || answer == 'D')
			{
				newCell->setArtifactPtr(nullptr);
				cout << "Artifact was destroyed" << endl;
			}
			system("pause");
			system("CLS");
			outputInfoOverMap(army);
			this->map->SetBackground("D");
			army = nullptr;
			
			Draw(this->turn, new_x, new_y);
		}
		if (hitTheWall == false && response == 1 || response == 3)
		{
			outputTurnSwitch(response);
			system("CLS");
			Army* army = nullptr;
			if (response == 3)
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
	ofstream ofs(this->LOG_PATH, std::ios_base::app);
	bool checker = ofs.is_open();
	if (checker == true)
	{
		time_t now = time(0);
		char str[26];
		ctime_s(str, sizeof str, &now);
		string dateTime = str;
		dateTime.erase(dateTime.size() - 1, dateTime.size());
		information = "\n" + information + " (" + dateTime + ")";
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
