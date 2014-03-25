//
//  Application.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Application.h"

namespace jewel {

Application::Application()
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
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
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
	
bool Application::process()
{
	static int wait = 0;
	handleInputs();
	updateWorld(1.0);
	SDL_Delay(1);
	++wait;
	if (wait>1000) return false;
	return true;
}
	
void Application::handleInputs()
{
	
}

void Application::updateWorld(float delta)
{
	scene->update(delta);
}
	
}