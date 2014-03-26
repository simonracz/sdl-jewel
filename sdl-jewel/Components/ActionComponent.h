//
//  ActionComponent.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionComponent__
#define __sdl_jewel__ActionComponent__

#include "Component.h"

namespace jewel {
	
class Action;
	
/**
 * ActionComponent
 *
 */
class ActionComponent : public artemis::Component {
public:
	Action* action{nullptr};
	
	ActionComponent(Action* action);
};
	
} //namespace



#endif /* defined(__sdl_jewel__ActionComponent__) */
