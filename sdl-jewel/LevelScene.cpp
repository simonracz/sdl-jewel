//
//  LevelScene.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "LevelScene.h"
#include "SDL2_image/SDL_image.h"
#include "World.h"

namespace jewel {

using namespace artemis;
	
const int LevelScene::TEXTURE_BG = 0;
const int LevelScene::TEXTURE_GEMS = 1;

LevelScene::LevelScene(SDL_Renderer* renderer) : renderer{renderer}
{
	assetManager = new AssetManager(renderer);
	assetManager->loadAssets();
	
	world = new World;
	
	createBgSprites();
	createEntities();
}
	
void LevelScene::createBgSprites()
{
	Sprite::setRenderer(renderer);
	
	bg = new Sprite(assetManager->getTexture(TEXTURE_BG));
	curtain = new Sprite(assetManager->getTexture(TEXTURE_BG), SDL_Rect{0,0,1024,192});
}
	
void LevelScene::createEntities()
{	
	SDL_Texture* gemTexture = assetManager->getTexture(TEXTURE_GEMS);
	Sprite* sprite = nullptr;
	int offsetX = 240;
	int offsetY = 192;
	for (int i=63; i>=0; --i) {
		if (table.getNode(i).type == NodeType::None)
			sprite = nullptr;
		else {
			sprite = new Sprite(gemTexture, srcRectToNodeType(table.getNode(i).type));
			gems.push_back(sprite);
		}
		int indexX = i % 8;
		int indexY = i/8;
		if (sprite) sprite->setPosition(offsetX + indexX*80, offsetY + indexY*80);
	}
}

SDL_Rect LevelScene::srcRectToNodeType(NodeType type)
{
	switch(type) {
		case NodeType::Blue:
			return SDL_Rect{0,0,40,40};
			break;
		case NodeType::Green:
			return SDL_Rect{40,0,40,40};
			break;
		case NodeType::Purple:
			return SDL_Rect{80,0,40,40};
			break;
		case NodeType::Red:
			return SDL_Rect{0,40,40,40};
			break;
		case NodeType::Yellow:
			return SDL_Rect{40,40,40,40};
			break;
		case NodeType::None:
			return SDL_Rect{0,0,0,0};
			break;
	}
}
	
LevelScene::~LevelScene()
{
	delete world;
	delete assetManager;
}

void LevelScene::update(float delta)
{
	/*
	world->loopStart();
	world->setDelta(delta);
	world->process();
*/
	
	SDL_RenderClear(renderer);
	bg->draw();
	for(auto sprite : gems) {
		sprite->draw(SDL_Rect{sprite->getPositionX(),sprite->getPositionY(), 80, 80});
	}
	SDL_RenderPresent(renderer);	
}

} //namespace