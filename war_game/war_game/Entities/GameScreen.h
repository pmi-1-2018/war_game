#pragma once
#include<SFML/Graphics.hpp>
#include"../Controllers/cScreen.h"
class GameScreen : public cScreen
{
public:
	GameScreen();
	virtual int Run(sf::RenderWindow &App, GameManager &gm);
};

