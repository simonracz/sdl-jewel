//
//  ActionSequence.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionSequence.h"

namespace jewel {

	
ActionSequence::ActionSequence(std::queue<Action*>& actions) : actions(actions)
{
	maxTime = 0; //we will calculate this during processing
}
	
bool ActionSequence::process(float delta, Sprite* sprite)
{
	totalTime+=delta;
	
	while ((delta>0) && (!actions.empty())) {
		if (!(actions.front()->process(delta,sprite))) {
			maxTime+=actions.front()->getMaxTime();
			actions.pop();
			delta = totalTime - maxTime;
		}
	}
	
	return actions.empty();
}
	
bool ActionSequence::isFinished()
{
	return actions.empty();
}

float ActionSequence::getMaxTime()
{
	return maxTime;
}
	
	
} //namespace