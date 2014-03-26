//
//  RenderingSystem.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "RenderingSystem.h"
#include "SDL2/SDL.h"
#include "Sprite.h"

namespace jewel {
	
RenderingSystem::RenderingSystem(SDL_Renderer* renderer, Sprite* bg, Sprite* curtain) : renderer(renderer), bg(bg), curtain(curtain)
{
	setComponentTypes<RenderingComponent>();
}

void RenderingSystem::initialize()
{
	rcMapper.init(*world);
}
	
void RenderingSystem::begin()
{
	SDL_RenderClear(renderer);
	bg->draw();
}
	
void RenderingSystem::processEntity(artemis::Entity &e)
{
	auto component = rcMapper.get(e);
	Sprite* sprite = component->sprite;
	SDL_SetTextureAlphaMod(sprite->getTexture(), sprite->getAlpha());
	sprite->draw(SDL_Rect{sprite->getPosX(),sprite->getPosY(), 80, 80});
	SDL_SetTextureAlphaMod(sprite->getTexture(), 255);
}
	
void RenderingSystem::end()
{
	curtain->draw(SDL_Rect{0,0,1024,192});
	SDL_RenderPresent(renderer);
}
	
} //namespace

