#pragma once
#include "../Entities/Map.h"
#include <conio.h>
#include "Windows.h"
#include <string>
#include <vector>
#include <iostream>
//#define DEBUG
using namespace std;

class GameManager
{
private:
	Map* map;
	char turn;
	const string MAP_PATH = "Utils\\Read_Edit_Map.txt";
	int mapHeight;
	int mapWidth;
	bool mapGenerated = false;
	bool gameStarted = false;
public:
	GameManager();
	void GenerateMap(int height, int width);
	void Draw()const;
	void Start(int height, int width);
	void SwitchTurn();
	bool MapIsGenerated()const;
	bool MoveChar(char symb, int x, int y);
	~GameManager();
};

