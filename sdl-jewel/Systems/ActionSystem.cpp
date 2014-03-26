//
//  ActionSystem.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "ActionSystem.h"
#include "Action.h"
#include "World.h"

namespace jewel {
	
using namespace artemis;
	
ActionSystem::ActionSystem()
{
	Action::initActions(this);
}

ActionSystem::~ActionSystem()
{
	
}

void ActionSystem::addAction(Action* action){
	actions.insert(action);
}

void ActionSystem::removeAction(Action* action)
{
	actions.erase(action);
}
void ActionSystem::removeAllActions()
{
	for (auto action : actions) {
		action->removeFromSprite();
		delete action;
	}
	actions.clear();
}
	
bool ActionSystem::checkProcessing()
{
	return true;
}

void ActionSystem::begin()
{
	
}
	
void ActionSystem::processEntities(ImmutableBag<Entity*> & bag)
{
	for(std::set<Action*>::iterator it = actions.begin(); it!= actions.end(); ++it) {
		if (!((*it)->process(world->getDelta()))) {
			(*it)->removeFromSprite();
			delete (*it);
			it = actions.erase(it);
		}
	}
}
	
void ActionSystem::end()
{
	
}
	
} //namespace