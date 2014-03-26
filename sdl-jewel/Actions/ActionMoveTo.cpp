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
	
ActionMoveTo::ActionMoveTo(float delay, int x, int y) : maxTime(delay)
{
	origX = sprite->getPosX();
	origY = sprite->getPosY();
	
	targetX = x;
	targetY = y;
}

bool ActionMoveTo::process(float delta, Sprite* sprite)
{
	Sprite *s = this->sprite;
	if (!s) s = sprite;
	
	totalTime+=delta;
	
	float d = totalTime / maxTime;
	
	//to prevent over sliding
	if (totalTime>=maxTime) {
		s->setPosition(targetX, targetY);
	} else {
		s->setPosition(origX + (targetX-origX)*d, origY + (targetY-origY)*d);
	}
	
	return (totalTime>=maxTime);
}

bool ActionMoveTo::isFinished()
{
	return (totalTime>=maxTime);
}
	
} //namespace