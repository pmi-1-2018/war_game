#pragma once
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
	GameManager* gm;
public:
	Menu();
	void PrintMenu()const;
	void MenuHint()const;
	void KeyHandler();
	void StartGame();
	void GenerateMap();
	bool EditMap();
	void ShowLog();
	void EndGame();
	~Menu();
};


