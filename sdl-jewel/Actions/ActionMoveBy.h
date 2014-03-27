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

class ActionMoveBy : public Action {
private:
	int origX;
	int origY;
	int targetX;
	int targetY;
	int x;
	int y;
	float totalTime{0};
	float maxTime;
protected:
	bool process(float delta) override;
	bool isFinished() override;
public:
	ActionMoveBy(float delay, int x, int y);
	
	void setSprite(Sprite* sprite) override;
	
	float getMaxTime() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionMoveBy__) */
