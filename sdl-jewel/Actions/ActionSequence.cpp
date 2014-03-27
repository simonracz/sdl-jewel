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

void ActionSequence::setSprite(Sprite* sprite)
{
	Action::setSprite(sprite);
	
	auto ac = actions->begin();
	if (ac != actions->end()) {
		(*ac)->setSprite(sprite);
	}
}
	
bool ActionSequence::process(float delta)
{
	totalTime+=delta;
	
	while ((delta>0) && (!actions->empty())) {
		if (!(actions->front()->process(delta))) {
			maxTime+=actions->front()->getMaxTime();
			delete actions->front();
			actions->pop_front();
			delta = totalTime - maxTime;
						
			if (!actions->empty()) {
				actions->front()->setSprite(sprite);
			}
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