#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include "Entities/Army.h"
#include "Utils/Menu.h"

//int main() 
//{
//	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
//	srand(time_ui);
//	Menu menu;
//	menu.PrintMenu();
//	menu.KeyHandler();
//	system("pause");
//	return 0;
//}
//"    Generate map\n      Start Game\n        Edit Map\n Show battle history\n            Exit"setPosition(Vector2f(window.getSize().x /2.f - 15* 6, window.getSize().y /2.f - 25 * menu_size)) ,25

using namespace sf;

int main()
{
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);
	
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(975, 480), "microChelik", Style::Default , settings);
	window.setVerticalSyncEnabled(true);
	
	Menu menu(window.getSize().x, window.getSize().y);
	menu.PrintMenu();
	
	Font font;
	font.loadFromFile("Utils/arial.ttf");

	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Utils/backgroundImage.png"); 
	
	Music backgroundMusic;
	backgroundMusic.openFromFile("Utils/Rampart.wav");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture); 
	backgroundSprite.setScale(sf::Vector2f(1.25f, 1.f)); 
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.scrollUp();
					break;
				case Keyboard::Down:
					menu.scrollDown();
					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(backgroundSprite);
		menu.Draw(window);
		window.display();
	}
	return 0;
}