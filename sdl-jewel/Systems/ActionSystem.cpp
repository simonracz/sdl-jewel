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
#include <iostream>

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
	std::cerr << "Action " << action->id << " will be added to the System\n";
	toBeAdded.insert(action);
}

void ActionSystem::removeAction(Action* action)
{
	std::cerr << "Action " << action->id << " will be removed from the System\n";
	toBeDeleted.erase(action);
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
	for (auto ac : toBeAdded) {
		std::cerr << "Action " << ac->id << " will be removed from Sprite\n";
		actions.insert(ac);
	}
	
	toBeAdded.clear();
}
	
void ActionSystem::processEntities(ImmutableBag<Entity*> & bag)
{
	for(std::set<Action*>::iterator it = actions.begin(); it!= actions.end(); ++it) {
		if (!((*it)->process(world->getDelta()))) {
			toBeDeleted.insert((*it));
		}
	}
}
	
void ActionSystem::end()
{
	for (auto ac : toBeDeleted) {
		std::cerr << "Action " << ac->id << " will be removed from Sprite\n";
		ac->removeFromSprite();
		delete ac;
		actions.erase(ac);
	}
	
	toBeDeleted.clear();
}
	
} //namespace