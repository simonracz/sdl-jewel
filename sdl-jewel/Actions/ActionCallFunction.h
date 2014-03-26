//
//  ActionCallFunction.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__ActionCallFunction__
#define __sdl_jewel__ActionCallFunction__

#include "Action.h"
#include <functional>

namespace jewel {

class ActionCallFunction : public Action {
private:
	std::function<void(void*)> fnct;
	void* payload;
	bool isFunctionCalled{false};
	float maxTime;
protected:
	bool process(float delta, Sprite* sprite = nullptr) override;
	bool isFinished() override;
public:
	ActionCallFunction(std::function<void(void*)> fnct, void* payload);

	float getMaxTime() override;
};
	
}

#endif /* defined(__sdl_jewel__ActionCallFunction__) */
