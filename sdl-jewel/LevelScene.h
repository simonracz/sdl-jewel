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
#include "InputHandler.h"

namespace artemis{
	class Entity;
	class World;
}

namespace jewel {

class LogicSystem;
	
/**
 * This class acts as a controller.
 * It's model is the Table class.
 *
 * In case of more scenes there would be a base Scene class and this class would be renamed to GameScene.
 */
class LevelScene : public InputDelegate {
private:
	Table table;
	//The first parameter is the table index.
	//It is possible that there is no entity for a given valid index
	//when the gems are falling, therefore this can't be a vector.
	std::map<int, artemis::Entity*> entities;
	Sprite* bg{nullptr};
	Sprite* curtain{nullptr};
	AssetManager* assetManager{nullptr};
	artemis::World* world{nullptr};
	InputHandler* inputHandler{nullptr};
	LogicSystem* logicSystem{nullptr};
	SDL_Renderer* renderer;
	bool hasSelection{false};
public:
	static const int TEXTURE_BG;
	static const int TEXTURE_GEMS;
	
	LevelScene(SDL_Renderer* renderer);
	
	void newEvent(SDL_Event* event);
	void nodeTouchedAt(int index) override;
	void nodeSlidTo(int index, Direction direction) override;
	
	~LevelScene();
	
	void update(float delta);
private:
	SDL_Rect srcRectToNodeType(NodeType type);
	void createEntities();
	void createBgSprites();
};
	
} //namespace

#endif /* defined(__sdl_jewel__LevelScene__) */
