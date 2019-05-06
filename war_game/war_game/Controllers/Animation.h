#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

struct Frame 
{
	sf::IntRect rect;
	double duration; // sec
};
class Animation 
{
	std::vector<Frame> frames;
	double totalLength;
	double progress;
	sf::Sprite &target;

public:
	Animation(sf::Sprite &target);
	void addFrame(Frame&& frame);
	void update(double elapsed);
};

