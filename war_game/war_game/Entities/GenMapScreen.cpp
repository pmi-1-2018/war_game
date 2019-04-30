#include"GenMapScreen.h"

GenMapScreen::GenMapScreen()
{
	int userHeight = 0;
	int userWidth = 0;
	output = new sf::Text[2];
	output[0].setString("Enter the height of the map(min 2) : " + userHeight);
	output[1].setString("Enter the width of the map(min 2) : " + userWidth);
}

int GenMapScreen::Run(sf::RenderWindow& App, GameManager &gm)
{
	bool running = true;

	for (int i = 0; i < 2; i++)
	{
		output[i].setFont(gm.getFont());
		output[i].setCharacterSize(25);
		output[i].setFillColor(sf::Color::Black);
		output[i].setPosition(sf::Vector2f(App.getSize().x / 2.f - 16 * 15, App.getSize().y / 10.f * (4 + i)));
	}
	
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Utils/backgroundImage.png");

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(sf::Vector2f(1.25f, 1.f));

	int index = 0;
	std::string userInput = "";
	
	
	
	while (running)
	{
		sf::Event event;
		output[0].setString("Enter the height of the map(min 2) : " + to_string(userHeight));
		output[1].setString("Enter the width of the map(min 2) : " + to_string(userWidth));
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return -1;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					return 0;
					break;
				case sf::Keyboard::Return:
					if (userInput == "" || stoi(userInput) < 2 || stoi(userInput) > 1000)
					{
						break;
					}
					if (index == 1)
					{
						userWidth = stoi(userInput);
						gm.GenerateMap(userHeight, userWidth);
						userHeight = 0;
						userWidth = 0;
						return 0;
					}
					if (index == 0)
					{
						userHeight = stoi(userInput);
						userInput = "";
						index++;
					}					
					break;
				case sf::Keyboard::BackSpace:
					if (userInput.length() != 0)
					{
						userInput.pop_back();
						if (userInput.length() == 0)
						{
							if (index == 0)
							{
								userHeight = 0;
							}
							if (index == 1)
							{
								userWidth = 0;
							}
						}
						else
						{
							if (index == 0)
							{
								userHeight = stoi(userInput);
							}
							if (index == 1)
							{
								userWidth = stoi(userInput);
							}
						}					
					}
					break;
				}
				break;
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (userInput.length() < 5)
				{
					if (47 < event.text.unicode && event.text.unicode < 58)
					{
						userInput += static_cast<char>(event.text.unicode);
						if (index == 0)
						{
							userHeight = stoi(userInput);
						}
						if (index == 1)
						{
							userWidth = stoi(userInput);
						}
					}
				}	
			}
		}
		App.clear();
		App.draw(backgroundSprite);
		if (index == 0)
		{
			App.draw(output[index]);
		}
		else
		{
			App.draw(output[0]);
			App.draw(output[1]);
		}
		App.display();
	}
	return -1;
}

GenMapScreen::~GenMapScreen()
{
	delete[] output;
}