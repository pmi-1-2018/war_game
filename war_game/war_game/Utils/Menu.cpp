#include "Menu.h"

Menu::Menu()
{
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
	this->gm->SetMusic("menu");
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
			system("CLS");
			PrintMenu();
			this->gm->SetMusic("menu");
			break;
		}
		case 51:
		{
			bool checker = EditMap();
			if (checker == true)
			{
				validKey = true;
			}
			else
			{
				PrintMenu();
				this->gm->SetMusic("Menu");
				continue;
			}
			break;
		}
		case 52:
		{
			validKey = true;
			ShowLog();
			PrintMenu();
			this->gm->SetMusic("Menu");
			continue;
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
	}
}

void Menu::StartGame()
{
	system("CLS");
	gm->Start();
}

void Menu::GenerateMap()
{
	system("CLS");
	cout << "###Generating The Map###" << endl << endl;
	cout << "Enter the height of the map: ";
	int height;
	cin >> height;
	cout << "Enter the width of the map: ";
	int width;
	cin >> width;
	gm->GenerateMap(height, width);
	cout << "Success!!" << endl;
	system("CLS");
	this->gm->SetBackground("");
	this->PrintMenu();
}

bool Menu::EditMap()
{
	system("CLS");
	cout << "###Map editing###" << endl << endl;
	if (this->gm->MapIsGenerated() == false) 
	{
		system("CLS");
		cout << "The map is not generated." << endl << "Would you like to generate it automatically? - y/n " << endl;
		char key = _getch();
		int asciiVal = key;
		if (asciiVal == 121)
		{
			//by default 10/10
			this->gm->GenerateMap(10, 10);
		}
		else 
		{
			system("CLS");
			this->gm->SetBackground("");
			return false;
		}
	}
	string mapPath = this->gm->GetMapPath();
	string request = "notepad " + mapPath;
	system(request.c_str());
	while (true)
	{
		system("CLS");
		cout << "###Map editing###" << endl << endl;
		cout << "Have you edited the map?" << endl << "y - back to the menu" << endl << "n - reopen the map" << endl;
		char key = _getch();
		int asciiVal = key;
		if (asciiVal == 121)
		{
			system("CLS");
			this->gm->MapFileSet();
			this->gm->SetBackground("");
			PrintMenu();
			break;

		}
		else {
			system("CLS");
			system(request.c_str());
			continue;
		}

	}
	return true;
}

void Menu::ShowLog()
{
	system("CLS");
	cout << "###History### " << endl << endl;
	string filePath = this->gm->GetLogPath();
	ifstream ifs(filePath);
	if (ifs.eof() == true) 
	{
		cout << "There were no battles yet" << endl;
		return;
	}
	else {
		string result = "";
		while (ifs.eof() == false) 
		{
			string temp;
			getline(ifs, temp);
			result += temp;
		}
		cout << result << endl;
		cout << "y - back to the menu" << endl;
		while (true) {
			char key = _getch();
			int asciiVal = key;
			if (asciiVal == 121)
			{
				system("CLS");
				ifs.close();
				return;
			}
		}
		
	}
}

void Menu::EndGame()
{
	exit(0);
}

Menu::~Menu()
{
	delete[] this->options;
}

