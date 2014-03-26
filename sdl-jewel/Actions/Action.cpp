//
//  Action.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Action.h"
#include "Sprite.h"
#include "ActionSystem.h"
#include "ActionMoveBy.h"
#include "ActionMoveTo.h"
#include "ActionWait.h"
#include "ActionAlphaTo.h"
#include "ActionCallFunction.h"
#include "ActionSequence.h"

namespace jewel {
	
std::set<int> Action::freeIds;
ActionSystem* Action::actionSystem;
	
void Action::initActions(ActionSystem* system)
{
	for (int i=0; i<1000; ++i) {
		freeIds.insert(i);
	}
	actionSystem = system;
}
	
Action::Action()
{
	id = *freeIds.begin();
	freeIds.erase(id);
}
	
Action::~Action()
{
	freeIds.insert(id);
}

void Action::setSprite(Sprite* sprite)
{
	this->sprite = sprite;
}
	
void Action::startAction()
{
	if (sprite) {
		actionSystem->addAction(this);
	}
}

void Action::pauseAction()
{
	actionSystem->removeAction(this);
}

void Action::removeFromSprite()
{
	if (sprite) {
		sprite->removeAction();
	}
}
	
void Action::setParentAction(Action* action){
	parentAction = action;
	setSprite(nullptr);
	actionSystem->removeAction(this);
}
	
Action* Action::wait(float delta)
{
	Action* action = new ActionWait(delta);
	return action;
}
Action* Action::moveBy(float delta, int x, int y)
{
	Action* action = new ActionMoveBy(delta, x, y);
	return action;
}
Action* Action::moveTo(float delta, int x, int y)
{
	Action* action = new ActionMoveTo(delta, x, y);
	return action;
}
Action* Action::alphaTo(float delta, int alpha)
{
	Action* action = new ActionAlphaTo(delta, alpha);
	return action;
}
Action* Action::callFunction(std::function<void(void*)> fnct, void* payload)
{
	Action* action = new ActionCallFunction(fnct, payload);
	return action;
}
Action* Action::sequence(std::deque<Action*>* actions)
{
	Action* action = new ActionSequence(actions);
	return action;
}
	
}