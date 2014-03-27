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
#include "SDL2_ttf/SDL_ttf.h"

namespace jewel {

class Sprite;
	
/**
 * RenderingSystem
 * This system is responsible for the visible state changes.
 */
class RenderingSystem : public artemis::EntityProcessingSystem {
public:
	RenderingSystem(SDL_Renderer* renderer, Sprite* bg, Sprite* curtain, TTF_Font* font);
	void initialize() override;
	
	void setScore(int score);
	void setTime(int time);
protected:
	void begin() override;
	void processEntity(artemis::Entity &e) override;
	void end() override;
private:
	artemis::ComponentMapper<RenderingComponent> rcMapper;
	Sprite* bg;
	Sprite* curtain;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color scoreFontColor;
	SDL_Color timeFontColor;
	SDL_Color gameOverColor;
	SDL_Rect destTimeRect;
	SDL_Rect destScoreRect;
	SDL_Rect gameOverRect;
	int score{0};
	int time{60};
	char buf[20];
	
	void initColors();
	void initDestRects();
};

	
} //namespace


#endif /* defined(__sdl_jewel__RenderingSystem__) */
