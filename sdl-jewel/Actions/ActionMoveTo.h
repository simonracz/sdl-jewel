//
//  ActionMoveTo.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionMoveTo__
#define __sdl_jewel__ActionMoveTo__

#include "Action.h"

namespace jewel {
	
class Sprite;

class ActionMoveTo : public Action {
private:
	int origX;
	int origY;
	int targetX;
	int targetY;
	float totalTime{0};
	float maxTime;
protected:
	bool process(float delta, Sprite* sprite = nullptr) override;
	bool isFinished() override;
public:
	ActionMoveTo(float delay, int x, int y);
	
	void setSprite(Sprite* sprite) override;
	float getMaxTime() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionMoveTo__) */
