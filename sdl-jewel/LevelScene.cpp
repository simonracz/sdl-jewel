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
	assetManager = new AssetManager(renderer);
	assetManager->loadAssets();
	//create Sprites/entities based on the table
	bg = new Sprite(assetManager->getTexture(0));
	Sprite::setRenderer(renderer);
	SDL_Texture* gemTexture = assetManager->getTexture(1);
	Sprite* sprite = nullptr;
	int offsetX = 240;
	int offsetY = 192;
	for (int i=63; i>=0; --i) {
		switch(table.getNode(i).type) {
			case NodeType::Blue:
				sprite = new Sprite(gemTexture, SDL_Rect{0,0,40,40});
				gems.push_back(sprite);
				break;
			case NodeType::Green:
				sprite = new Sprite(gemTexture, SDL_Rect{40,0,40,40});
				gems.push_back(sprite);
				break;
			case NodeType::Purple:
				sprite = new Sprite(gemTexture, SDL_Rect{80,0,40,40});
				gems.push_back(sprite);
				break;
			case NodeType::Red:
				sprite = new Sprite(gemTexture, SDL_Rect{0,40,40,40});
				gems.push_back(sprite);
				break;
			case NodeType::Yellow:
				sprite = new Sprite(gemTexture, SDL_Rect{40,40,40,40});
				gems.push_back(sprite);
				break;
			case NodeType::None:
				sprite = nullptr;
				break;
		}
		int indexX = i % 8;
		int indexY = i/8;
		if (sprite) sprite->setPosition(offsetX + indexX*80, offsetY + indexY*80);
	}
}

LevelScene::~LevelScene()
{
	delete bg;
	delete assetManager;
}

bool LevelScene::update(float delta)
{
	SDL_RenderClear(renderer);
	bg->draw();
	for(auto sprite : gems) {
		sprite->draw(SDL_Rect{sprite->getPositionX(),sprite->getPositionY(), 80, 80});
	}
	SDL_RenderPresent(renderer);
	return true;
}

} //namespace