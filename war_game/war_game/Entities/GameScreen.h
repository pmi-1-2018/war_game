#pragma once
#include<SFML/Graphics.hpp>
#include "../Controllers/Animation.h"
#include"../Controllers/cScreen.h"
class GameScreen : public cScreen
{
public:
	GameScreen();
	virtual int Run(sf::RenderWindow& App, GameManager& gm);
	//void updateAnim(Animation& anim, sf::RenderWindow& App, GameManager &gm);
	void addFramesToAnim(std::vector<Animation>& bothPlayersAnims, int offset);
};

