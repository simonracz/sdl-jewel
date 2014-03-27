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
	
RenderingSystem::RenderingSystem(SDL_Renderer* renderer, Sprite* bg, Sprite* curtain, TTF_Font* font) : renderer(renderer), bg(bg), curtain(curtain), font(font)
{
	setComponentTypes<RenderingComponent>();
	fontColor.a = 255;
	fontColor.r = 240;
	fontColor.g = 200;
	fontColor.b = 210;
	
	destScoreRect.x = 560;
	destScoreRect.y = 96;
	destScoreRect.w = 320;
	destScoreRect.h = 96;	
}

void RenderingSystem::initialize()
{
	rcMapper.init(*world);
}
	

void RenderingSystem::setScore(int score)
{
	this->score = score;
}

void RenderingSystem::setTime(int time)
{
	this->time = time;
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
	
	sprintf(buf, "%4d", score);
	SDL_Surface *surf = TTF_RenderText_Blended(font, buf, fontColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_RenderCopy(renderer, texture, NULL, &destScoreRect);
	SDL_RenderPresent(renderer);
}
	
} //namespace

