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
#include "Action.h"

namespace jewel {
	
class ActionSystem : public artemis::EntitySystem {
public:
	ActionSystem();
	~ActionSystem();
protected:
	bool checkProcessing() override;

	void begin() override;
	void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag) override;
	void end() override;
private:
	
};
	
} //namespace

#endif /* defined(__sdl_jewel__ActionSystem__) */
