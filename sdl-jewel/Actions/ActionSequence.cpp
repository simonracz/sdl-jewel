//
//  ActionSequence.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionSequence.h"

namespace jewel {

	
ActionSequence::ActionSequence(std::deque<Action*>* actions) : actions(actions)
{
	for (auto action : *actions) {
		action->setParentAction(this);
	}
	maxTime = 0; //we will calculate this during processing
}
	
ActionSequence::~ActionSequence()
{
	for (auto action : *actions) {
		delete action;
	}
	delete actions;
}
	
bool ActionSequence::process(float delta, Sprite* sprite)
{
	totalTime+=delta;
	
	while ((delta>0) && (!actions->empty())) {
		if (!(actions->front()->process(delta,sprite))) {
			maxTime+=actions->front()->getMaxTime();
			delete actions->front();
			actions->pop_front();
			delta = totalTime - maxTime;
		} else {
			delta = 0;
		}
	}
	
	return !(actions->empty());
}
	
bool ActionSequence::isFinished()
{
	return actions->empty();
}

float ActionSequence::getMaxTime()
{
	return maxTime;
}
	
	
} //namespace