#include "EditMapScreen.h"



EditMapScreen::EditMapScreen():
	selectedOptionIndex(0)
{
	yes_no = new sf::Text[2];
	yes_no[0].setString("Yes");
	yes_no[1].setString("No");
}

int EditMapScreen::Run(sf::RenderWindow &App, GameManager &gm)
{
	if (gm.MapIsGenerated() == false)
	{
		GenMapScreen tempGenMapScreen;
		int val = tempGenMapScreen.Run(App, gm);
		if (val == -1)
		{
			return -1;
		}
	}

	bool running = true;

	for (int i = 0; i < 2; i++)
	{
		yes_no[i].setFont(gm.getFont());
		yes_no[i].setCharacterSize(25);
	}
	yes_no[0].setFillColor(sf::Color::Yellow);
	yes_no[1].setFillColor(sf::Color::Black);
	yes_no[0].setPosition(sf::Vector2f(App.getSize().x / 2.f - 60, App.getSize().y / 10.f * 6));
	yes_no[1].setPosition(sf::Vector2f(App.getSize().x / 2.f + 60, App.getSize().y / 10.f * 6));

	sf::Text output;
	output.setFont(gm.getFont());
	output.setCharacterSize(25);
	output.setString("Have you edited the map?");
	output.setFillColor(sf::Color::Black);
	output.setPosition(sf::Vector2f(App.getSize().x / 2.f - (15 * 8), App.getSize().y / 10.f * 4));
	
	std::string mapPath = gm.GetMapPath();
	std::string request = "notepad " + mapPath;

	system(request.c_str());

	while (running)
	{
		sf::Event event;
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
					if (selectedOptionIndex == 0)
					{
						gm.MapFileSet();
						return 0;
					}
					else 
					{
						system(request.c_str());
					}
					break;
				case sf::Keyboard::Left:
					if (selectedOptionIndex - 1 >= 0)
					{
						yes_no[selectedOptionIndex].setFillColor(sf::Color::Black);
						selectedOptionIndex--;
						yes_no[selectedOptionIndex].setFillColor(sf::Color::Yellow);
					}
					break;
				case sf::Keyboard::Right:
					if (selectedOptionIndex + 1 < 2)
					{
						yes_no[selectedOptionIndex].setFillColor(sf::Color::Black);
						selectedOptionIndex++;
						yes_no[selectedOptionIndex].setFillColor(sf::Color::Yellow);
					}
					break;
				}
			}
		}
		App.clear();
		App.draw(gm.getBackgroundSprite());
		App.draw(output);
		for (int i = 0; i < 2; i++)
		{
			App.draw(yes_no[i]);
		}
		App.display();
	}
	return -1;
}

EditMapScreen::~EditMapScreen()
{
	delete[] yes_no;
}
