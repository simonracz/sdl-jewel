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
#include "Entity.h"
#include "RenderingSystem.h"
#include "ActionSystem.h"
#include "RenderingComponent.h"
#include "Action.h"
#include "LogicSystem.h"

namespace jewel {

using namespace artemis;
	
LevelScene::LevelScene(SDL_Renderer* renderer) : renderer{renderer}
{
	assetManager = new AssetManager(renderer);
	assetManager->loadAssets();
	createBgSprites();
	
	world = new World;
	logicSystem = new LogicSystem(&table, assetManager, bg, this);
	inputHandler = new InputHandler(logicSystem);
	logicSystem->setInputHandler(inputHandler);
	world->addSystem(logicSystem);
	renderingSystem = new RenderingSystem(renderer, bg, curtain);
	renderingSystem->setTime(gameTime);
	renderingSystem->setScore(gameScore);
	world->addSystem(renderingSystem);
	world->addSystem(new ActionSystem);
	world->initialize();
	
	createEntities();
}
	
void LevelScene::createBgSprites()
{
	Sprite::setRenderer(renderer);
	
	bg = new Sprite(assetManager->getTexture(AssetManager::TEXTURE_BG));
	curtain = new Sprite(assetManager->getTexture(AssetManager::TEXTURE_BG), SDL_Rect{0,0,1024,192});
}
	
void LevelScene::addScore(int score)
{
	gameScore+=score;
	renderingSystem->setScore(gameScore);
}
	
void LevelScene::createEntities()
{
	SDL_Texture* gemTexture = assetManager->getTexture(AssetManager::TEXTURE_GEMS);
	Sprite* sprite = nullptr;
	int offsetX = 240;
	int offsetY = 192;
	for (int i=63; i>=0; --i) {
		sprite = new Sprite(gemTexture, LogicSystem::srcRectToNodeType(table.getNode(i).type));
		int indexX = i % 8;
		int indexY = i/8;
		sprite->setPosition(offsetX + indexX*80, offsetY + indexY*80);
		Entity& entity = world->createEntity();
		entity.addComponent(new RenderingComponent(sprite));
		entity.refresh();
		logicSystem->addEntity(i, &entity);
	}
}
	
void LevelScene::newEvent(SDL_Event* event)
{
	inputHandler->newEvent(event);
}
	
LevelScene::~LevelScene()
{
	delete inputHandler;
	delete world;
	delete assetManager;
}

void LevelScene::begin()
{
	gameStartTime = std::chrono::high_resolution_clock::now();
}
	
void LevelScene::update(float delta)
{
	world->loopStart();
	world->setDelta(delta);
	world->process();
	
	using namespace std::chrono;
	
	renderingSystem->setTime(60 - static_cast<int>((duration_cast<duration<double>>(high_resolution_clock::now() - gameStartTime)).count()));
}

} //namespace