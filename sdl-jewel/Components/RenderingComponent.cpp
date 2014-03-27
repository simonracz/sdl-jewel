//
//  RenderingComponent.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "RenderingComponent.h"

namespace jewel {

RenderingComponent::RenderingComponent(Sprite* sprite) : sprite(sprite)
{
	//empty
}

RenderingComponent::~RenderingComponent()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}
	
} //namespace