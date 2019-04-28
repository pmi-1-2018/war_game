#include <iostream>
#include <string>
#include <ctime>
#include "Entities/Army.h"
#include "Utils/Menu.h"
using namespace std;

int main() 
{
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);
	Menu menu;
	menu.PrintMenu();
	menu.KeyHandler();
	system("pause");
	return 0;
}


// USE CODE BELOW TO TEST IF SFML WORKS PROPERLY


//#include <SFML/Graphics.hpp>
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}