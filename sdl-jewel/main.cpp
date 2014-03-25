//
//  main.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 23/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Application.h"

int main( int argc, char* args[] )
{
	using namespace jewel;
	
	Application app;

	if (!app.init()) {
		std::cerr << app.initError();
		return 1;
	}
	
	while (app.process()) {
		//empty
	}
    
	std::cout << "Done\n";
    return 0;
}

