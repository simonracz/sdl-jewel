//
//  ActionWait.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionWait__
#define __sdl_jewel__ActionWait__

#include "Action.h"

namespace jewel {

class ActionWait : public Action {
private:
	float totalTime{0};
	float maxTime;
protected:
	bool process(float delta) override;
	bool isFinished() override;
public:
	ActionWait(float delay);

	float getMaxTime() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionWait__) */
