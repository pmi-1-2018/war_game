#include"GenMapScreen.h"

GenMapScreen::GenMapScreen()
{
	int userHeight = 0;
	int userWidth = 0;
	output = new sf::Text[2];
	output[0].setString("Enter the height of the map(min 2) : " + userHeight);
	output[1].setString("Enter the width of the map(min 2) : " + userWidth);
	/*selectedOptionIndex = 0;
	yes_no = new sf::Text[2];
	yes_no[0].setString("Yes");
	yes_no[1].setString("No");*/
}

int GenMapScreen::Run(sf::RenderWindow& App, GameManager &gm)
{
	bool runnig = true;
	
	sf::Font font;
	font.loadFromFile("Utils/arial.ttf");

	/*for (int i = 0; i < 2; i++)
	{
		yes_no[i].setFont(font);
		yes_no[i].setCharacterSize(25);
	}*/
	for (int i = 0; i < 2; i++)
	{
		output[i].setFont(font);
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
	
	
	
	while (runnig)
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
						std::cout << (char)event.text.unicode;
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