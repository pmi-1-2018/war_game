#pragma once
#include <SFML/Graphics.hpp>
#include "../Entities/Map.h"
#include <conio.h>
#include "Windows.h"
#include "MMSystem.h"
#include <string>
#include <fstream>
#include <iostream>
//#define DEBUG
using namespace std;

enum responseCases { hitObstacle, movedSuccessfully, hitPlayer, outOfPoints, enteredBarrack, enteredGoldMine };

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
	int numberOfTurn = 1;
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
public:
	GameManager();
	void GenerateMap(int height, int width);
	void Draw(const char& turn, int x, int y)const;
	void DrawMap(sf::Sprite& mapSprite, sf::RenderWindow& App);
	void Start();
	void FileLogW(string information);
	void SwitchTurn();
	string GetLogPath()const;
	string GetMapPath()const;
	bool RestartGame();
	void MapFileSet();
	void SetBackground(string flag);
	string StartBattle(Army* a1, Army* a2);
	bool MapIsGenerated()const;
	int MoveChar(char symb, Cell* prevCell, Cell* newCell);
	void SetMusic(const string& filename);
	void outputTurnSwitch(int response);
	void outputInfoOverMap(Army *army);
	sf::Font& getFont();
	sf::Sprite& getBackgroundSprite();
	~GameManager();
};

// response = 0 - hit the obstacle
// response = 1 - moved successfully
// response = 2 - hit the player, begining of the battle
// response = 3 - out of points - switching the turn
// response = 4 - stepped on a barrack
// response = 5 - stepped on a Gold Mine