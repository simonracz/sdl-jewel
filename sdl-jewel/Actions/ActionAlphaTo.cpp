//
//  ActionAlphaTo.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionAlphaTo.h"
#include "Sprite.h"

namespace jewel {
	
ActionAlphaTo::ActionAlphaTo(float delay, int alpha) : targetAlpha(alpha), maxTime(delay)
{
	//empty
}

void ActionAlphaTo::setSprite(Sprite* sprite)
{
	Action::setSprite(sprite);
	
	if (sprite) {
		origAlpha = sprite->getAlpha();
	}
}

bool ActionAlphaTo::process(float delta)
{
	totalTime+=delta;
	
	float d = totalTime / maxTime;
	
	//to prevent over sliding
	if (totalTime>=maxTime) {
		sprite->setAlpha(targetAlpha);
	} else {
		sprite->setAlpha(origAlpha + (targetAlpha-origAlpha)*d);
	}
	
	return (totalTime<maxTime);
}

float ActionAlphaTo::getMaxTime()
{
	return maxTime;
}

bool ActionAlphaTo::isFinished()
{
	return (totalTime>=maxTime);
}
	
} //namespace