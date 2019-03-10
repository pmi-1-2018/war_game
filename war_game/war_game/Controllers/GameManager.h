#pragma once
#include "../Entities/Map.h"
#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class GameManager
{
private:
	Map* map;
	char turn;
	const string MAP_PATH = "Utils\\Read_Edit_Map.txt";
	int mapHeight;
	int mapWidth;
public:
	GameManager();
	void GenerateMap(int height, int width);
	void Draw()const;
	void Start(int height, int width);
	void SwitchTurn();
	bool MoveChar(char symb, int x, int y);
	~GameManager();
};

