//
//  ActionMoveTo.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionMoveTo.h"
#include "Sprite.h"

namespace jewel {
	
ActionMoveTo::ActionMoveTo(float delay, int x, int y) : targetX(x), targetY(y), maxTime(delay)
{
	//empty
}
	
void ActionMoveTo::setSprite(Sprite* sprite)
{
	Action::setSprite(sprite);
	
	if (sprite) {
		origX = sprite->getPosX();
		origY = sprite->getPosY();
	}
}

bool ActionMoveTo::process(float delta)
{
	totalTime+=delta;
	
	float d = totalTime / maxTime;
	
	//to prevent over sliding
	if (totalTime>=maxTime) {
		sprite->setPosition(targetX, targetY);
	} else {
		sprite->setPosition(origX + (targetX-origX)*d, origY + (targetY-origY)*d);
	}
	
	return (totalTime<maxTime);
}

float ActionMoveTo::getMaxTime()
{
	return maxTime;
}
	
bool ActionMoveTo::isFinished()
{
	return (totalTime>=maxTime);
}
	
} //namespace