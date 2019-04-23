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
	const int OPT_COUNT = 6;
	string* options = new string[OPT_COUNT]{ "Generate map", "Start Game", "Edit Map", "Show battle history", "Exit", "Sandbox" };
	GameManager* gm;
public:
	Menu();
	void PrintMenu()const;
	void MenuHint()const;
	void KeyHandler();
	void StartGame();
	void Sandbox();
	void GenerateMap();
	bool EditMap();
	void ShowLog();
	void EndGame();
	~Menu();
};


