#include "MenuScreen.h"

MenuScreen::MenuScreen()
{
	menuOptions[0].setString("Generate map");
	menuOptions[1].setString("Start Game");
	menuOptions[2].setString("Edit Map");
	menuOptions[3].setString("Show battle history");
	menuOptions[4].setString("Exit");
}

int MenuScreen::Run(sf::RenderWindow &App, GameManager &gm)
{
	bool running = true;

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Utils/backgroundImage.png");

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(sf::Vector2f(1.25f, 1.f));

	for (int i = 0; i < OPT_COUNT; i++)
	{
		menuOptions[i].setFont(gm.getFont());
		menuOptions[i].setFillColor(sf::Color::Black);
		menuOptions[i].setCharacterSize(25);
		menuOptions[i].setPosition(sf::Vector2f((App.getSize().x / 2.f - 15 * 6), (App.getSize().y / (OPT_COUNT * 2.f)) * (2 + i)));
	}
	menuOptions[selectedOptionIndex].setFillColor(sf::Color::Yellow);
	
	sf::Event event;
	
	while (running)
	{
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return (-1);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (selectedOptionIndex - 1 >= 0)
					{
						menuOptions[selectedOptionIndex].setFillColor(sf::Color::Black);
						selectedOptionIndex--;
						menuOptions[selectedOptionIndex].setFillColor(sf::Color::Yellow);
					}
					break;
				case sf::Keyboard::Down:
					if (selectedOptionIndex + 1 < OPT_COUNT)
					{
						menuOptions[selectedOptionIndex].setFillColor(sf::Color::Black);
						selectedOptionIndex++;
						menuOptions[selectedOptionIndex].setFillColor(sf::Color::Yellow);
					}
					break;
				case sf::Keyboard::Return:
					switch (selectedOptionIndex)
					{
					case 0:
						return 1;
						break;
					case 1:
						return 2;
						break;
					case 2:
						return 3;
						break;
					case 3:
						return 4;
						break;
					case 4:
						return -1;
						break;
					}
					break;
				}		
			}
		}
		App.clear();
		App.draw(backgroundSprite);
		for (int i = 0; i < OPT_COUNT; i++)
		{
			App.draw(menuOptions[i]);
		}
		App.display();
	}

	return (-1);
}

MenuScreen::~MenuScreen()
{
	delete[] menuOptions;
}