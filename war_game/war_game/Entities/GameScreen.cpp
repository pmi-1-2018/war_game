#include "GameScreen.h"

GameScreen::GameScreen()
{
}

int GameScreen::Run(sf::RenderWindow &App, GameManager &gm)
{
	//sf::View view;
	/*view.setSize(sf::Vector2f(975, 480));
	view.setCenter(sf::Vector2f(0, 0));*/
	if (!gm.MapIsGenerated())
	{
		gm.GenerateMap(20, 20);
	}
	bool running = true;
	sf::Sprite mapSprite;
	gm.InitPlayers();
	int x_1 = 1;
	int y_1 = 0;
	int x_2 = gm.getMapWidth() - 2;
	int y_2 = gm.getMapHeight() - 1;
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
					return -1;
					break;
				case sf::Keyboard::W:
					gm.movePlayer(UP, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					
					break;
				case sf::Keyboard::A:
					gm.movePlayer(LEFT, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					
					break;
				case sf::Keyboard::D:
					gm.movePlayer(RIGHT, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					break;
				case sf::Keyboard::S:
					gm.movePlayer(DOWN, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					break;
				}
			}
			/*if (event.type == sf::Event::MouseMoved)
			{
			
			}*/
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				App.setView(sf::View(visibleArea));
			}
			App.clear();
			//App.setView(view);
			gm.DrawMap(mapSprite, App);
			App.display();
		}
	}
	return -1;
}