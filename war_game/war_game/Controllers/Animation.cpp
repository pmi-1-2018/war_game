#include "Animation.h"



Animation::Animation(sf::Sprite &target) : target(target)
{
	progress = totalLength = 0.0;
}


void Animation::addFrame(Frame&& frame) 
{
	totalLength += frame.duration;
	frames.push_back(std::move(frame));
}


void Animation::update(double elapsed)
{
	progress += elapsed;
	double modifProg = progress;
	for (size_t i = 0; i < frames.size(); i++) 
	{
		modifProg -= frames[i].duration;
		if (modifProg <= 0.0 || &(frames[i]) == &frames.back())
		{
			target.setTextureRect(frames[i].rect);
			if (modifProg >= 0.0 && &(frames[i]) == &(frames.back()))
			{
				i = 0;
				continue;
			}
			break;
		}
		
	}
}

double Animation::getTotalLength()
{
	return totalLength;
}
