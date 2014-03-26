//
//  ActionWait.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionWait.h"

namespace jewel {
	
ActionWait::ActionWait(float delay) : maxTime(delay)
{
	//empty
}

bool ActionWait::process(float delta, Sprite* sprite)
{
	totalTime+=delta;
	return (totalTime<maxTime);
}

float ActionWait::getMaxTime()
{
	return maxTime;
}

bool ActionWait::isFinished()
{
	return (totalTime>=maxTime);
}
	
} //namespace