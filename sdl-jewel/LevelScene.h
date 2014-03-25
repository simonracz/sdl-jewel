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
#include <vector>
#include "AssetManager.h"

namespace jewel {

class LevelScene {
private:
	Table table;
	Sprite* bg{nullptr};
	SDL_Renderer* renderer;
	AssetManager* assetManager;
	
	//demo
	std::vector<Sprite*> gems;
public:
	LevelScene(SDL_Renderer* renderer);
	
	~LevelScene();
	
	bool update(float delta);
};
	
} //namespace

#endif /* defined(__sdl_jewel__LevelScene__) */
