#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <vector>
#include "Controllers/Screens.hpp"
#include "Controllers/GameManager.h"


#define ZAEBIS 0
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
	
	std::vector<cScreen*> Screens;
	int screen = 0;

	GameManager gm;

	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(975, 480), "microChelik", Style::Default , settings);
	window.setVerticalSyncEnabled(true);

	sf::Music backgroundMusic;
	backgroundMusic.openFromFile("Utils/Rampart.wav");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	
	GenMapScreen genMapScreen;
	MenuScreen menuScreen;
	EditMapScreen editMapScreen;

	Screens.push_back(&menuScreen);
	Screens.push_back(&genMapScreen);
	Screens.push_back(&editMapScreen);
	Screens.push_back(&editMapScreen);
	
	
	while (screen >= 0)
	{
		/*if (screen != 0)
		{
			cout << screen << endl;
			screen = 0;
			continue;
		}*/
		screen = Screens[screen]->Run(window, gm);
	}
	
	/*Menu menu(window.getSize().x, window.getSize().y);
	menu.PrintMenu();*/
	//
	//while (window.isOpen())
	//{
	//	Event event;
	//	while (window.pollEvent(event))
	//	{
	//		switch (event.type)
	//		{
	//		case Event::KeyPressed:
	//			switch (event.key.code)
	//			{
	//			case Keyboard::Up:
	//				menu.scrollUp();
	//				break;
	//			case Keyboard::Down:
	//				menu.scrollDown();
	//				break;
	//			case Keyboard::Return:
	//				switch (menu.getSelectedOptionIndex())
	//				{
	//				case 0:
	//					break;
	//				case 1:
	//					break;
	//				case 2:
	//					//menu.EditMapREMAKE();
	//					break;
	//				case 3:
	//					break;
	//				case 4:
	//					break;
	//				}
	//				break;
	//			}
	//			break;
	//		case Event::Closed:
	//			window.close();
	//			break;
	//		}
	//	}
	//	window.clear();
	//	window.draw(backgroundSprite);
	//	menu.Draw(window);
	//	window.display();
	//}
	return ZAEBIS;
}