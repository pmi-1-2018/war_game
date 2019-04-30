#pragma once
//#include <SFML/Graphics.hpp>
//#include"../Controllers/cScreen.h"
#include"GenMapScreen.h"

class EditMapScreen : public cScreen
{
private:
	sf::Text *yes_no;
	int selectedOptionIndex;
public:
	EditMapScreen();
	virtual int Run(sf::RenderWindow &App, GameManager &gm);
	~EditMapScreen();
};

