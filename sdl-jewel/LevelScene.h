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

namespace artemis{
	class Entity;
	class World;
}

namespace jewel {

class LogicSystem;
class InputHandler;

/**
 * This class acts as a controller.
 * It's model is the Table class.
 *
 * In case of more scenes there would be a base Scene class and this class would be renamed to GameScene.
 */
class LevelScene {
private:
	Table table;
	Sprite* bg{nullptr};
	Sprite* curtain{nullptr};
	AssetManager* assetManager{nullptr};
	artemis::World* world{nullptr};
	InputHandler* inputHandler{nullptr};
	LogicSystem* logicSystem{nullptr};
	SDL_Renderer* renderer;
public:
	static const int TEXTURE_BG;
	static const int TEXTURE_GEMS;
	
	LevelScene(SDL_Renderer* renderer);
	
	void newEvent(SDL_Event* event);

	
	~LevelScene();
	
	void update(float delta);
private:
	SDL_Rect srcRectToNodeType(NodeType type);
	void createEntities();
	void createBgSprites();
};
	
} //namespace

#endif /* defined(__sdl_jewel__LevelScene__) */
