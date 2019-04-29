#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "../Controllers/GameManager.h"
using namespace std;
class Menu
{
private:
	const int OPT_COUNT = 5;
	string* options = new string[OPT_COUNT]{ "Generate map", "Start Game", "Edit Map", "Show battle history", "Exit" };
	//sf::Text *menuOptions = new sf::Text[OPT_COUNT];
	GameManager* gm;
	//sf::Font font;
	//int selectedOptionIndex = 0;
public:
	Menu(/*int width, int height*/);
	void PrintMenu()const;
	void MenuHint()const;
	void KeyHandler();
	void StartGame();
	void GenerateMap();
	bool EditMap();
	void ShowLog();
	void EndGame();
	//void scrollDown();
	//void scrollUp();
	//int getSelectedOptionIndex();
	//void Draw(sf::RenderWindow& window);
	/*bool EditMapREMAKE()
	{
		if (this->gm->MapIsGenerated() == false)
		{
			sf::Text warning("The map is not generated. Would you like to generate it automatically? - y/n", font, 25);
			
		}
	}*/
	/*void keyHandlerREMAKE(sf::Event& event)
	{
		bool checker;
		bool validKey = false;
		switch (event.key.code)
		{
		case sf::Keyboard::Num1:
			GenerateMap();
			break;
		case sf::Keyboard::Num2:
			StartGame();
			system("CLS");
			PrintMenu();
			this->gm->SetMusic("menu");
			break;
		case sf::Keyboard::Num3:
			checker = EditMap();
			if (checker == true)
			{
				validKey = true;
			}
			else
			{
				PrintMenu();
				this->gm->SetMusic("Menu");
	
			}
			break;
		case sf::Keyboard::Num4:
			validKey = true;
			ShowLog();
			PrintMenu();
			this->gm->SetMusic("Menu");
			break;
		case sf::Keyboard::Num5:
			validKey = true;
			EndGame();
			break;
		default:
			cout << "Incorrect key was pressed." << endl;
			MenuHint();
			break;
		}
	}*/
	~Menu();
};


