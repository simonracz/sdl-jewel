//
//  ActionSequence.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionSequence__
#define __sdl_jewel__ActionSequence__

#include "Action.h"

namespace jewel {

class ActionSequence : public Action {
private:
	std::deque<Action*>* actions;
	float totalTime{0};
	float maxTime;
protected:
	bool process(float delta, Sprite* sprite = nullptr) override;
	bool isFinished() override;
public:
	ActionSequence(std::deque<Action*>* actions);
	~ActionSequence();
	
	float getMaxTime() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionSequence__) */
