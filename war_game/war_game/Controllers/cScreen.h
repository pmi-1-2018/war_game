#pragma once
#include<SFML/Graphics.hpp>
#include"GameManager.h"

class cScreen
{
public:
	virtual int Run(sf::RenderWindow &App, GameManager &gm) = 0;
};