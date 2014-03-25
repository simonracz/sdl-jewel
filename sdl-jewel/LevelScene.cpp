//
//  LevelScene.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "LevelScene.h"
#include "SDL2_image/SDL_image.h"

namespace jewel {

LevelScene::LevelScene(SDL_Renderer* renderer) : renderer{renderer}
{
	
	//create Sprites/entities based on the table
	SDL_Texture* texture = IMG_LoadTexture(renderer, "/Users/simon/Dev/_git/sdl-jewel/sdl-jewel/Assets/bg.png");
	bg = new Sprite(texture);
	Sprite::setRenderer(renderer);
}

LevelScene::~LevelScene()
{
	delete bg;
}

bool LevelScene::update(float delta)
{
	SDL_RenderClear(renderer);
	bg->draw();
	SDL_RenderPresent(renderer);
	return true;
}

} //namespace