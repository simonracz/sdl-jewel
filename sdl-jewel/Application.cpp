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
	
}
	
bool Application::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		return false;
	}
	
	if (SDL_CreateWindowAndRenderer(1024, 1024, SDL_WINDOW_OPENGL, &window, &renderer)!=0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't start window or renderer.");
	}
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, 1024, 1024);
	
	scene = new LevelScene(renderer);
	
	return true;
}
	
std::string Application::initError()
{
	return SDL_GetError();
}
	
Application::~Application()
{
	delete scene;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
	
bool Application::process()
{
	static int wait = 0;
	handleInputs();
	updateWorld(1.0);
	SDL_Delay(1);
	++wait;
	if (wait>3000) return false;
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