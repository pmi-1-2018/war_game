#include "GameManager.h"


GameManager::GameManager() 
{
}
void GameManager::GenerateMap(int height, int width)
{
	this->mapHeight = height;
	this->mapWidth = width;
	map = new Map();
	map->generateRandomMap(this->MAP_PATH, mapHeight, mapWidth);
	this->mapGenerated = true;
	cout << "Notice! Map was generated. Now you can start playing." << endl;
	#ifdef DEBUG
		for (int i = 0; i < map->getHeight(); i++)
		{
			for (int j = 0; j < map->getWidth(); j++)
			{
				if (map->getIspassable(i, j) == false)
				{
					cout << i << " " << j << endl;
				}
			}
		}
	#endif
}
void GameManager::Draw()const
{
	cout << *(this->map);
}
void GameManager::SwitchTurn()
{
	if (this->turn == 'l')
	{
		this->turn = 'r';
	}
	else
	{
		this->turn = 'l';
	}
}
bool GameManager::MapIsGenerated() const
{
	return this->mapGenerated;
}
bool GameManager::MoveChar(char symb, int x, int y) 
{
	#ifdef DEBUG
		cout << "Moved " << symb << " to " << x << " " << y << endl;
	#endif
	bool response = map->setPlayer(symb, x, y);
	return response;
	
}
GameManager::~GameManager()
{
	delete map;
}
void GameManager::Start(int height, int width)
{
	if (this->mapGenerated == false)
	{
		GenerateMap(10, 10);
	}
	
	this->mapHeight = height;
	this->mapWidth = width;
	// mapheight - y, mapwidth - x
	
		Draw();
		int x_1 = 0;
		int y_1 = 0;
		int x_2 = mapWidth-1;
		int y_2 = mapHeight-1;
		turn = 'l';
		while (true)
		{
			int prev_x = turn == 'l' ? x_1 : x_2;
			int prev_y = turn == 'l' ? y_1 : y_2;
			bool hitTheWall = false;
			char key;
			int asciiValue;
			key = _getch();
			asciiValue = key;
			if (asciiValue == 97)
			{
				if (turn == 'l') {
					if (x_1 != 0) {
						x_1 -= 1;
					}
					else 
					{
						hitTheWall = true;
					}
				}
				else 
				{
					if (x_2 != 0) {
						x_2 -= 1;
					}
					else 
					{
						hitTheWall = true;
					}
				}
			}
			else if (asciiValue == 100)
			{
				if (turn == 'l') {
					if (x_1 != mapHeight-1) {
						x_1 += 1;
					}
					else 
					{
						hitTheWall = true;
					}
				}
				else
				{
					if (x_2 != mapHeight - 1) {
						x_2 += 1;
					}
					else 
					{
						hitTheWall = true;
					}
				}
			}
			else if (asciiValue == 119)
			{
				if (turn == 'l') {
					if (y_1 != 0) {
						y_1 -= 1;
					}
					else
					{
						hitTheWall = true;
					}
				}
				else
				{
					if (y_2 != 0) {
						y_2 -= 1;
					}
					else
					{
						hitTheWall = true;
					}
				}
			}
			else if (asciiValue == 115)
			{
				if (turn == 'l') {
					if (y_1 != mapWidth - 1) {
						y_1 += 1;
					}
					else
					{
						hitTheWall = true;
					}
				}
				else
				{
					if (y_2 != mapWidth - 1) {
						y_2 += 1;
					}
					else
					{
						hitTheWall = true;
					}
				}
			}
			else if (asciiValue == 27)
			{
				break;
			}
			char symb = turn == 'l' ? '*' : '$';
			int& new_x = turn == 'l' ? x_1 : x_2;
			int& new_y = turn == 'l' ? y_1 : y_2;

			bool response = MoveChar(symb, new_x, new_y);
			if (response == false) 
			{
				new_x = prev_x;
				new_y = prev_y;
				continue;
			}
			if (hitTheWall == false)
			{
				system("CLS");
				SwitchTurn();
				cout << "Turn: " << this->turn << endl;
				Draw();
			}
		}
	
}