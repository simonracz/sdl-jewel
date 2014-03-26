//
//  RenderingSystem.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__RenderingSystem__
#define __sdl_jewel__RenderingSystem__

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"
#include "RenderingComponent.h"

namespace jewel {

class Sprite;
	
/**
 * RenderingSystem
 * This system is responsible for the visible state changes.
 */
class RenderingSystem : public artemis::EntityProcessingSystem {
public:
	RenderingSystem(SDL_Renderer* renderer, Sprite* bg, Sprite* curtain);
	void initialize() override;
protected:
	void begin() override;
	void processEntity(artemis::Entity &e) override;
	void end() override;
private:
	artemis::ComponentMapper<RenderingComponent> rcMapper;
	Sprite* bg;
	Sprite* curtain;
	SDL_Renderer* renderer;
};

	
} //namespace


#endif /* defined(__sdl_jewel__RenderingSystem__) */
