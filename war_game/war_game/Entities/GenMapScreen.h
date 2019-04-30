#pragma once
#include<SFML/Graphics.hpp>
#include"../Controllers/cScreen.h"
#include<string>

class GenMapScreen : public cScreen
{
private:
	sf::Text *output;
	int userHeight;
	int userWidth;
	/*sf::Text *yes_no;
	int selectedOptionIndex;*/
public:
	GenMapScreen();
	virtual int Run(sf::RenderWindow &App, GameManager &gm);
};

