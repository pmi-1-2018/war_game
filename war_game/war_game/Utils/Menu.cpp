#include "Menu.h"

//class Unit
//{
//	int danger;
//
//};
//class Army
//{
//	vector<Unit> units;
//public:
//	char symb;
//};

//Draw map
//void outMap(vector<vector<int>> arr, int x = 0, int y = 0) {
//
//	for (int i = 0; i < arr.size(); ++i) {
//		for (int j = 0; j < arr.size(); ++j) {
//			if (j == x && i == y) {
//				cout << "#" << " ";
//			}
//			else if (arr[i][j] == 0) {
//				cout << 0 << " ";
//			}
//			else {
//				cout << '.' << " ";
//			}
//		}
//
//		cout << endl;
//	}
//}

//            Here we are starting our game
//void startGame(Army army, vector<vector<int>> arr)
//{
//	int x = 0;
//	int y = 0;
//	while (true)
//	{
//		char key;
//		int asciiValue;
//		key = _getch();
//		asciiValue = key;
//		if (asciiValue == 97)
//		{
//			if (x != 0)
//				x -= 1;
//		}
//		else if (asciiValue == 100)
//		{
//			if (x != arr.size() - 1)
//				x += 1;
//		}
//		else if (asciiValue == 119)
//		{
//			if (y != 0)
//				y -= 1;
//		}
//		else if (asciiValue == 115)
//		{
//			if (y != arr.size() - 1)
//				y += 1;
//		}
//		else if (asciiValue == 27)
//		{
//			break;
//		}
//		outMap(arr, x, y);
//	}
//}

Menu::Menu()
{
	this->errorState = 0;
	gm = new GameManager();
}

void Menu::PrintMenu()const
{
	cout << "###WarGame###" << endl;
	cout << "Main menu" << endl << endl;
	for (int i = 0; i < this->OPT_COUNT; i++)
	{
		cout << i + 1 << ") " << this->options[i] << endl;
	}
	MenuHint();
}

void Menu::MenuHint() const
{
	cout << "[Use keys 1-" << this->OPT_COUNT + 1 << " to interact with the menu]" << endl;
}

void Menu::KeyHandler()
{
	char key;
	int asciiValue;
	while (true)
	{
		key = _getch();
		asciiValue = key;
		bool validKey = false;
		switch (asciiValue)
		{
		case 49:
		{
			GenerateMap();
			break;
		}
		case 50:
		{
			validKey = true;
			StartGame();
			break;
		}
		case 51:
		{
			validKey = true;
			EditMap();
			break;
		}
		case 52:
		{
			validKey = true;
			ShowLog();
			break;
		}
		case 53:
		{
			validKey = true;
			EndGame();
			break;
		}
		default:
		{
			cout << "Incorrect key was pressed." << endl;
			MenuHint();
		}
		}
		if (validKey == true)
		{
			break;
		}

	}
}

void Menu::StartGame()
{
	system("CLS");
	gm->Start(10, 10);
}

void Menu::GenerateMap()
{
	gm->GenerateMap(10, 10);
}

void Menu::EditMap()
{
	cout << "You can now edit the map" << endl;
}

void Menu::ShowLog()
{
	cout << "History of the last fights" << endl;
}

void Menu::EndGame()
{
	exit(0);
}

