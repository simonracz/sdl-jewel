//
//  ActionSequence.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionSequence.h"
#include <iostream>

namespace jewel {
	
ActionSequence::ActionSequence(std::initializer_list<Action*> actions)
{
	for (auto it = actions.begin(); it!=actions.end();++it) {
		(*it)->setParentAction(this);
		(this->actions).push(*it);
	}
	maxTime = 0; //we will calculate this during processing
}
	
ActionSequence::~ActionSequence()
{
	while (!actions.empty()) {
		delete actions.front();
		actions.pop();
	}
}

void ActionSequence::setSprite(Sprite* sprite)
{
	Action::setSprite(sprite);
	if (!actions.empty()) {
		std::cerr << "setSprite\n";
		actions.front()->setSprite(sprite);
	}
}
	
bool ActionSequence::process(float delta)
{
	totalTime+=delta;
	
	while ((delta>0) && (!actions.empty())) {
		if (!(actions.front()->process(delta))) {
			maxTime+=actions.front()->getMaxTime();
			delete actions.front();
			actions.pop();
			delta = totalTime - maxTime;
						
			if (!actions.empty()) {
				std::cerr << "setSprite in loop\n";
				actions.front()->setSprite(sprite);
			}
		} else {
			delta = 0;
		}
	}
	
	return !(actions.empty());
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