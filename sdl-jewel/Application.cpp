//
//  Application.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include <iostream>
#include "Application.h"

namespace jewel {

const int Application::FRAMES_PER_SECOND = 30;
	
Application::Application() : fps(1.0 / static_cast<double>(FRAMES_PER_SECOND))
{
	//empty
}
	
bool Application::init()
{
	if (!initSDL()) {
		return false;
	}
	
	scene = new LevelScene(renderer);
	
	return true;
}
	
bool Application::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
		return false;
	}
	preInitFinished = true;
	
	window = SDL_CreateWindow("Jewel",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  1024, 1024,
							  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create the window.");
		return false;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create the renderer.");
		return false;
	}
	
	/*
	if (SDL_CreateWindowAndRenderer(1024, 1024, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer)!=0) {
	 SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and/or renderer.");
	 return false;
	}*/
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, 1024, 1024);
	
	return true;
}
	
std::string Application::initError()
{
	return SDL_GetError();
}
	
Application::~Application()
{
	delete scene;
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	if (preInitFinished) {
		SDL_Quit();
	}
}
	
void Application::begin()
{
	lastFrameStartTime = std::chrono::steady_clock::now();
	gameStartTime = std::chrono::steady_clock::now();
}

bool Application::process()
{
	using namespace std::chrono;
	
	frameStartTime = std::chrono::steady_clock::now();
	
	if (!handleInputs()) {
		return false;
	}

	updateWorld((duration_cast<duration<float>>(steady_clock::now() - lastFrameStartTime)).count());

	delta = (duration_cast<duration<double>>(steady_clock::now() - frameStartTime)).count();
	
	if (delta < fps) {
		SDL_Delay((fps - delta) * 1000);
	}
	
	lastFrameStartTime = frameStartTime;
	
	return true;
}

void Application::end()
{
	using namespace std::chrono;
	
	std::cout << "The game run for " << ((duration_cast<duration<double>>(steady_clock::now() - gameStartTime)).count()) << " seconds.\n";
}
	
bool Application::handleInputs()
{
	static int wait = 0;
	++wait;
	if (wait>300) return false;
	return true;
}

void Application::updateWorld(float delta)
{
	scene->update(delta);
}
	
}