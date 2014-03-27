//
//  RenderingComponent.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__RenderingComponent__
#define __sdl_jewel__RenderingComponent__

#include "Component.h"
#include "Sprite.h"

namespace jewel {
	
/**
 * RenderingComponent
 *
 * The gem always bound to one and only one field, even when it visually seem to be between two fields.
 * The Sprite's inner position is used for rendering.
 */
class RenderingComponent : public artemis::Component {
public:
	Sprite* sprite;
	bool selected{false};
	Uint8 alpha{255};
	
	RenderingComponent(Sprite* sprite);
	~RenderingComponent();
};
	
} //namespace

#endif /* defined(__sdl_jewel__RenderingComponent__) */
