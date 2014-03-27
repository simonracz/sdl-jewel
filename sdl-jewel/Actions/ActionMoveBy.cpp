//
//  ActionMoveBy.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionMoveBy.h"
#include "Sprite.h"

namespace jewel {

ActionMoveBy::ActionMoveBy(float delay, int x, int y) : x(x), y(y), maxTime(delay)
{
	//empty
}
	
void ActionMoveBy::setSprite(Sprite* sprite)
{
	Action::setSprite(sprite);
	
	if (sprite) {
		origX = sprite->getPosX();
		origY = sprite->getPosY();
		
		targetX = origX + x;
		targetY = origY + y;
	}
}

bool ActionMoveBy::process(float delta)
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

float ActionMoveBy::getMaxTime()
{
	return maxTime;
}
	
bool ActionMoveBy::isFinished()
{
	return (totalTime>=maxTime);
}

} //namespace