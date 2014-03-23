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
	
	return true;
}
	
std::string Application::initError()
{
	return SDL_GetError();
}
	
Application::~Application()
{
	SDL_Quit();
}
	
bool Application::process()
{
	return false;
}
	
void Application::handleInputs()
{
	
}

void Application::updateWorld(float delta)
{
	
}
	
}