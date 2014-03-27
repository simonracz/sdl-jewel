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

void RenderingSystem::setScore(int score)
{
	std::cout << "game score : " << score << "\n";
}

void RenderingSystem::setTime(int time)
{
	//std::cerr << "game time : " << time << "\n";
}
	
void RenderingSystem::processEntity(artemis::Entity &e)
{
	auto component = rcMapper.get(e);
	Sprite* sprite = component->sprite;
	if (component->selected) {
		SDL_SetTextureColorMod(sprite->getTexture(), 180, 120, 120);
	}
	SDL_SetTextureAlphaMod(sprite->getTexture(), sprite->getAlpha());
	sprite->draw(SDL_Rect{sprite->getPosX(),sprite->getPosY(), 80, 80});
	SDL_SetTextureAlphaMod(sprite->getTexture(), 255);
	if (component->selected) {
		SDL_SetTextureColorMod(sprite->getTexture(), 255, 255, 255);
	}
}
	
void RenderingSystem::end()
{
	curtain->draw(SDL_Rect{0,0,1024,192});
	SDL_RenderPresent(renderer);
}
	
} //namespace

