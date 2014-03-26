//
//  LogicSystem.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__LogicSystem__
#define __sdl_jewel__LogicSystem__

#include "EntitySystem.h"

namespace jewel {
	
class Action;

class LogicSystem : public artemis::EntitySystem {
public:
	LogicSystem();
	~LogicSystem();
	
	void setProcessing(bool process);
protected:
	bool checkProcessing() override;
	
	void begin() override;
	void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag) override;
	void end() override;
private:
	bool processing{true};
};
	
} //namespace


#endif /* defined(__sdl_jewel__LogicSystem__) */
