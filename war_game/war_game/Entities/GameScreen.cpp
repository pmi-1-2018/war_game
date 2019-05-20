#include "GameScreen.h"

GameScreen::GameScreen()
{
}

int GameScreen::Run(sf::RenderWindow& App, GameManager& gm)
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
	
	sf::Sprite& player1 = gm.getMapPtr()->GetCell(x_1, y_1)->GetArmy()->getArmyCharacter();
	sf::Sprite& player2 = gm.getMapPtr()->GetCell(x_2, y_2)->GetArmy()->getArmyCharacter();

	int offset = 290;
	//addFramesToAnim(, 290);

	Animation player_1UP(player1);
	player_1UP.addFrame({ sf::IntRect(15,7,32,35), 0.3 });
	player_1UP.addFrame({ sf::IntRect(75,6,32,35), 0.3 });
	player_1UP.addFrame({ sf::IntRect(132,6,32,35), 0.3 });
	
	Animation player_1DOWN(player1);
	player_1DOWN.addFrame({ sf::IntRect(8,63,31,35), 0.3 });
	player_1DOWN.addFrame({ sf::IntRect(67,62,31,36), 0.3 });
	player_1DOWN.addFrame({ sf::IntRect(127,62,31,36), 0.3 });

	Animation player_1LEFT(player1);
	player_1LEFT.addFrame({ sf::IntRect(18,115,14,36), 0.3 });
	player_1LEFT.addFrame({ sf::IntRect(80,115,14,36), 0.3 });
	player_1LEFT.addFrame({ sf::IntRect(141,116,14,36), 0.3 });

	Animation player_1RIGHT(player1);
	player_1RIGHT.addFrame({ sf::IntRect(18,167,12,36), 0.3 });
	player_1RIGHT.addFrame({ sf::IntRect(82,167,11,36), 0.3 });
	player_1RIGHT.addFrame({ sf::IntRect(141,167,13,36), 0.3 });

	Animation player_2UP(player2);
	player_2UP.addFrame({ sf::IntRect(offset + 15,7,32,35), 0.3 });
	player_2UP.addFrame({ sf::IntRect(offset + 75,6,32,35), 0.3 });
	player_2UP.addFrame({ sf::IntRect(offset + 132,6,32,35), 0.3 });

	Animation player_2DOWN(player2);
	player_2DOWN.addFrame({ sf::IntRect(offset + 8,63,31,35), 0.3 });
	player_2DOWN.addFrame({ sf::IntRect(offset + 67,62,31,36), 0.3 });
	player_2DOWN.addFrame({ sf::IntRect(offset + 127,62,31,36), 0.3 });

	Animation player_2LEFT(player2);
	player_2LEFT.addFrame({ sf::IntRect(offset + 18,115,14,36), 0.3 });
	player_2LEFT.addFrame({ sf::IntRect(offset + 80,115,14,36), 0.3 });
	player_2LEFT.addFrame({ sf::IntRect(offset + 141,116,14,36), 0.3 });

	Animation player_2RIGHT(player2);
	player_2RIGHT.addFrame({ sf::IntRect(offset + 18,167,12,36), 0.3 });
	player_2RIGHT.addFrame({ sf::IntRect(offset + 82,167,11,36), 0.3 });
	player_2RIGHT.addFrame({ sf::IntRect(offset + 141,167,13,36), 0.3 });

	sf::Clock animationCL;
	sf::Time animationTime;
	sf::Clock elapsedCL;
	sf::Time elapsed;
	int animDirection = AFK;
	
	int counter = 1;

	while (running)
	{
		elapsed = elapsedCL.restart();
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
					//gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					animationCL.restart();
					animDirection = UP;
					//updateAnim(player_1UP, time);
					break;
				case sf::Keyboard::A:
					gm.movePlayer(LEFT, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					animationCL.restart();
					animDirection = LEFT;
					break;
				case sf::Keyboard::D:
					gm.movePlayer(RIGHT, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					animationCL.restart();
					animDirection = RIGHT;
					break;
				case sf::Keyboard::S:
					gm.movePlayer(DOWN, x_1, y_1, x_2, y_2);
					gm.setPlayerSpritePosition(x_1, y_1, x_2, y_2);
					animationCL.restart();
					animDirection = DOWN;
					break;
				}
			}
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				App.setView(sf::View(visibleArea));
			}
		}
		animationTime = animationCL.getElapsedTime();
		if (animationTime.asSeconds() < player_1UP.getTotalLength())
		{
			if (gm.getTurn() == 'F')
			{
				switch (animDirection)
				{
				case UP:
					player_1UP.update(elapsed.asSeconds());
					player1.setPosition(player1.getPosition() -4 );
					break;
				case LEFT:
					player_1LEFT.update(elapsed.asSeconds());
					break;
				case RIGHT:
					player_1RIGHT.update(elapsed.asSeconds());
					break;
				case DOWN:
					player_1DOWN.update(elapsed.asSeconds());
					break;
				}
			}
			else
			{
				switch (animDirection)
				{
				case UP:
					player_2UP.update(elapsed.asSeconds());
					break;
				case LEFT:
					player_2LEFT.update(elapsed.asSeconds());
					break;
				case RIGHT:
					player_2RIGHT.update(elapsed.asSeconds());
					break;
				case DOWN:
					player_2DOWN.update(elapsed.asSeconds());
					break;
				}
			}
		}
		App.clear();
		//App.setView(view);
		gm.DrawMap(mapSprite, App);
		App.display();
	}
	return -1;
}

//void GameScreen::addFramesToAnim(std::vector<Animation>& bothPlayersAnims, int offset)
//{
//	//first player anims
//
//	bothPlayersAnims[0].addFrame({ sf::IntRect(15,7,32,35), 0.3 });
//	bothPlayersAnims[0].addFrame({ sf::IntRect(75,6,32,35), 0.3 });
//	bothPlayersAnims[0].addFrame({ sf::IntRect(132,6,32,35), 0.3 });
//
//	bothPlayersAnims[1].addFrame({ sf::IntRect(8,63,31,35), 0.3 });
//	bothPlayersAnims[1].addFrame({ sf::IntRect(67,62,31,36), 0.3 });
//	bothPlayersAnims[1].addFrame({ sf::IntRect(127,62,31,36), 0.3 });
//
//	bothPlayersAnims[2].addFrame({ sf::IntRect(18,115,14,36), 0.3 });
//	bothPlayersAnims[2].addFrame({ sf::IntRect(80,115,14,36), 0.3 });
//	bothPlayersAnims[2].addFrame({ sf::IntRect(141,116,14,36), 0.3 });
//
//	bothPlayersAnims[3].addFrame({ sf::IntRect(18,167,12,36), 0.3 });
//	bothPlayersAnims[3].addFrame({ sf::IntRect(82,167,11,36), 0.3 });
//	bothPlayersAnims[3].addFrame({ sf::IntRect(141,167,13,36), 0.3 });
//
//	//second 
//
//	bothPlayersAnims[4].addFrame({ sf::IntRect(offset + 15,7,32,35), 0.3 });
//	bothPlayersAnims[4].addFrame({ sf::IntRect(offset + 75,6,32,35), 0.3 });
//	bothPlayersAnims[4].addFrame({ sf::IntRect(offset + 132,6,32,35), 0.3 });
//
//	bothPlayersAnims[5].addFrame({ sf::IntRect(offset + 8,63,31,35), 0.3 });
//	bothPlayersAnims[5].addFrame({ sf::IntRect(offset + 67,62,31,36), 0.3 });
//	bothPlayersAnims[5].addFrame({ sf::IntRect(offset + 127,62,31,36), 0.3 });
//
//	bothPlayersAnims[6].addFrame({ sf::IntRect(offset + 18,115,14,36), 0.3 });
//	bothPlayersAnims[6].addFrame({ sf::IntRect(offset + 80,115,14,36), 0.3 });
//	bothPlayersAnims[6].addFrame({ sf::IntRect(offset + 141,116,14,36), 0.3 });
//
//	bothPlayersAnims[7].addFrame({ sf::IntRect(offset + 18,167,12,36), 0.3 });
//	bothPlayersAnims[7].addFrame({ sf::IntRect(offset + 82,167,11,36), 0.3 });
//	bothPlayersAnims[7].addFrame({ sf::IntRect(offset + 141,167,13,36), 0.3 });
//}


//void GameScreen::updateAnim(Animation& anim, sf::RenderWindow& App, GameManager &gm)
//{
//	sf::Clock cl;
//	sf::Time elapsed;
//	bool animating = true;
//	while (animating)
//	{
//		elapsed = cl.restart();
//		animating = anim.update(elapsed.asSeconds());
//		App.clear();
//		//gm.DrawMap(mapSprite, App);
//		//App.draw()
//	}
//}