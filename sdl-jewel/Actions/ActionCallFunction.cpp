//
//  ActionCallFunction.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionCallFunction.h"

namespace jewel {

ActionCallFunction::ActionCallFunction(std::function<void(void*)> fnct, void* payload) : fnct(fnct), payload(payload), maxTime(0.0)
{
	//empty
}
	
bool ActionCallFunction::process(float delta, Sprite* sprite)
{
	fnct(payload);
	
	isFunctionCalled = true;
	return false;
}
	
bool ActionCallFunction::isFinished()
{
	return isFunctionCalled;
}
	
float ActionCallFunction::getMaxTime()
{
	return maxTime;
}
	
}