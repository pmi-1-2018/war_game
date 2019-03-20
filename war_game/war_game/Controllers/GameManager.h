#pragma once
#include "../Entities/Map.h"
#include <conio.h>
#include "Windows.h"
#include <string>
#include <fstream>
#include <iostream>
//#define DEBUG
using namespace std;

class GameManager
{
private:
	Map* map;
	char turn;
	const string MAP_PATH = "Utils\\Read_Edit_Map.txt";
	const string LOG_PATH = "Utils\\log.txt";
	int mapHeight;
	int mapWidth;
	bool mapGenerated = false;
	bool gameStarted = false;
public:
	GameManager();
	void GenerateMap(int height, int width);
	void Draw()const;
	void Start();
	void FileLogW(string information);
	void SwitchTurn();
	string GetLogPath()const;
	string GetMapPath()const;
	void RestartGame();
	void SetBackground(string flag);
	string StartBattle()const;
	bool MapIsGenerated()const;
	int MoveChar(char symb, int x, int y);
	~GameManager();
};

