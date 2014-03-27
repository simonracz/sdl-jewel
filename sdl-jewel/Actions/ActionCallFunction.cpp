//
//  ActionCallFunction.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionCallFunction.h"
#include <iostream>

namespace jewel {

ActionCallFunction::ActionCallFunction(std::function<void(void)> fnct) : fnct(fnct), maxTime(0.0)
{
	//empty
}
	
bool ActionCallFunction::process(float delta)
{
	fnct();

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