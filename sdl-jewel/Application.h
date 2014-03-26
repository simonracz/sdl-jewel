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
#include <chrono>
#include "SDL2/SDL.h"
#include "LevelScene.h"

namespace jewel {

class Application {
	SDL_Window* window{nullptr};
	SDL_Renderer* renderer{nullptr};
	LevelScene* scene{nullptr};
	std::chrono::high_resolution_clock::time_point gameStartTime;
	std::chrono::steady_clock::time_point frameStartTime;
	std::chrono::steady_clock::time_point lastFrameStartTime;
	double fps;
	double delta;
public:
	Application();
	~Application();
	bool init();
	std::string initError();
	
	static const int FRAMES_PER_SECOND;

	void begin();
	bool process();
	void end();
private:
	bool handleInputs();
	void update(float delta);
	
	bool initSDL();
	bool preInitFinished{false};
};
	
} //namespace

#endif /* defined(__sdl_jewel__Application__) */
