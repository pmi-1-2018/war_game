#pragma once
#include"../Controllers/cScreen.h"
#include<SFML/Audio.hpp>

class MenuScreen :public cScreen
{
private:
	const int OPT_COUNT = 5;
	sf::Text *menuOptions = new sf::Text[OPT_COUNT];
	int selectedOptionIndex = 0;
public:
	MenuScreen();
	virtual int Run(sf::RenderWindow &App, GameManager &gm);
};

