//
//  ActionAlphaTo.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionAlphaTo__
#define __sdl_jewel__ActionAlphaTo__

#include "Action.h"

namespace jewel {

class ActionAlphaTo : public Action {
private:
	int origAlpha;
	int targetAlpha;
	float totalTime{0};
	float maxTime;
protected:
	bool process(float delta) override;
	bool isFinished() override;
public:
	ActionAlphaTo(float delay, int alpha);
	
	void setSprite(Sprite* sprite) override;
	float getMaxTime() override;
};
	
}
#endif /* defined(__sdl_jewel__ActionAlphaTo__) */
