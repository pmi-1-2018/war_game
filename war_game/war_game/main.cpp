#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <vector>
#include "Controllers/Screens.hpp"
#include "Controllers/GameManager.h"


#define ZAEBIS 0

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
	RenderWindow window(VideoMode(975, 480), "MACROASSEMBLER", Style::Default , settings);
	window.setVerticalSyncEnabled(true);

	sf::Music backgroundMusic;
	backgroundMusic.openFromFile("Utils/Rampart.wav");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	GenMapScreen genMapScreen;
	MenuScreen menuScreen;
	EditMapScreen editMapScreen;
	GameScreen gameScreen;
	
	Screens.push_back(&menuScreen);
	Screens.push_back(&genMapScreen);
	Screens.push_back(&gameScreen);
	Screens.push_back(&editMapScreen);
	
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window, gm);
	}
	return ZAEBIS;
}