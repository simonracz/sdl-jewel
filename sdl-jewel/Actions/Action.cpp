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
	if (sprite) {
		actionSystem->addAction(this);
	} else {
		actionSystem->removeAction(this);
	}
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
}
	
}