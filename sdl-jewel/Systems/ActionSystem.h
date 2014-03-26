//
//  ActionSystem.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionSystem__
#define __sdl_jewel__ActionSystem__

#include "EntitySystem.h"
#include <set>

namespace jewel {

class Action;
	
class ActionSystem : public artemis::EntitySystem {
public:
	ActionSystem();
	~ActionSystem();

	void addAction(Action* action);
	/**
	 * This does not delete the action
	 * It shouldn't be called by user code
	 * Call Sprite::removeAction() instead
	 */
	void removeAction(Action* action);
	/**
	 * Removes and deletes all actions.
	 */
	void removeAllActions();
protected:
	bool checkProcessing() override;

	void begin() override;
	void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag) override;
	void end() override;
private:
	std::set<Action*> actions;
};
	
} //namespace

#endif /* defined(__sdl_jewel__ActionSystem__) */
