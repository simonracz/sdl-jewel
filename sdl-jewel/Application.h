//
//  Application.h
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__Application__
#define __sdl_jewel__Application__

#include <string>
#include "SDL2/SDL.h"
#include "LevelScene.h"

namespace jewel {

class Application {
	SDL_Window* window{nullptr};
	SDL_Renderer* renderer{nullptr};
	LevelScene* scene{nullptr};
	//Timer* timer;
	//World* world;
public:
	Application();
	~Application();
	
	const int FRAMES_PER_SECOND = 30;
	
	bool init();
	bool process();
	
	std::string initError();
	
private:
	void handleInputs();
	void updateWorld(float delta);
};
	
} //namespace

#endif /* defined(__sdl_jewel__Application__) */
