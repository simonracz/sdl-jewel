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

int main( int argc, char* args[] )
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
    //Quit SDL
	SDL_Quit();
    
	std::cout << "Done" << std::endl;
    return 0;
}

