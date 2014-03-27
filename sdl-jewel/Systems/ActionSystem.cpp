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
	//std::cerr << "Action " << action->id << " will be added to the System\n";
	if (toBeDeleted.count(action) != 0 ) {
		toBeDeleted.erase(action);
	}
	toBeAdded.insert(action);
}

void ActionSystem::removeAction(Action* action)
{
	//std::cerr << "Action " << action->id << " will be removed from the System\n";
	if (toBeAdded.count(action) != 0) {
		toBeAdded.erase(action);
	} else {
		toBeDeleted.insert(action);
	}
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
		//std::cerr << "Action " << ac->id << " added to ActionSystem\n";
		actions.insert(ac);
	}
	
	toBeAdded.clear();
}
	
void ActionSystem::processEntities(ImmutableBag<Entity*> & bag)
{
	for(std::set<Action*>::iterator it = actions.begin(); it!= actions.end(); ++it) {
		if ((toBeDeleted.count(*it)==0) && !((*it)->process(world->getDelta()))) {
			toBeDeleted.insert(*it);
		}
	}
}
	
void ActionSystem::end()
{
	for (auto ac : toBeDeleted) {
		if (actions.count(ac)==0) continue;
		
		//std::cerr << "Action " << ac->id << " removed from ActionSystem\n";
		ac->removeFromSprite();
		delete ac;
		actions.erase(ac);
	}
	
	toBeDeleted.clear();
}
	
} //namespace