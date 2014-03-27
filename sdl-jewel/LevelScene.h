//
//  LevelScene.h
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__LevelScene__
#define __sdl_jewel__LevelScene__

#include "Table.h"
#include "Sprite.h"
#include <map>
#include "AssetManager.h"
#include "ScoreDelegate.h"
#include <chrono>

namespace artemis{
	class Entity;
	class World;
}

namespace jewel {

class LogicSystem;
class InputHandler;
class RenderingSystem;
	
/**
 * This class acts as a controller.
 * It's model is the Table class.
 *
 * In case of more scenes there would be a base Scene class and this class would be renamed to GameScene.
 */
class LevelScene : public ScoreDelegate {
private:
	Table table;
	Sprite* bg{nullptr};
	Sprite* curtain{nullptr};
	AssetManager* assetManager{nullptr};
	artemis::World* world{nullptr};
	InputHandler* inputHandler{nullptr};
	LogicSystem* logicSystem{nullptr};
	RenderingSystem* renderingSystem{nullptr};
	SDL_Renderer* renderer;
	std::chrono::high_resolution_clock::time_point gameStartTime;
	int gameScore{0};
	int gameTime{60};
public:
	LevelScene(SDL_Renderer* renderer);
	
	void newEvent(SDL_Event* event);
	
	~LevelScene();
	
	void addScore(int score) override;
	
	void begin();
	void update(float delta);
private:
	void createEntities();
	void createBgSprites();
};
	
} //namespace

#endif /* defined(__sdl_jewel__LevelScene__) */
