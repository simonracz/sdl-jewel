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
#include <queue>

namespace jewel {

class ActionSequence : public Action {
private:
	std::queue<Action*> actions;
	float totalTime{0};
	float maxTime;
protected:
	bool process(float delta) override;
	bool isFinished() override;
public:
	ActionSequence(std::initializer_list<Action*> actions);
	~ActionSequence();
	
	void setSprite(Sprite* sprite) override;
	
	float getMaxTime() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionSequence__) */
