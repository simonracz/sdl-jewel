//
//  ActionMoveBy.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionMoveBy__
#define __sdl_jewel__ActionMoveBy__

#include "Action.h"

namespace jewel {
	
class Sprite;
	
class ActionMoveBy : public Action {
private:
	int targetX;
	int targetY;
	int origX;
	int origY;
	float totalTime{0};
	float maxTime;
protected:
	ActionMoveBy(float delay, int x, int y);
	
	bool process(float delta, Sprite* sprite = nullptr) override;
	bool isFinished() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionMoveBy__) */
