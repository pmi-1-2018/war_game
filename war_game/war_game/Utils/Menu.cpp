#include "Menu.h"

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

