//
//  InputHandler.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__InputHandler__
#define __sdl_jewel__InputHandler__

#include "SDL2/SDL.h"
#include "Table.h"

namespace jewel {
	
class InputDelegate {
public:
	virtual void nodeTouchedAt(int index) = 0;
	virtual void nodeSlidTo(int index, Direction direction) = 0;
};
	
class LogicSystem;

class InputHandler {
	Table* table;
	InputDelegate* delegate;
	bool ignoreEvents{false};
	static const int offsetX;
	static const int offsetY;
	static const int moveTreshhold;
public:
	InputHandler(InputDelegate* delegate, Table* table);
	
	void setProcessing(bool process);
	
	void newEvent(SDL_Event* e);
private:
	bool isInsideTableBounds(SDL_Event* e);
	int indexForEvent(SDL_Event* e);
	bool directionForMouseEvent(SDL_Event* e, Direction* direction, int* index);
};
	
} //namespace

#endif /* defined(__sdl_jewel__InputHandler__) */
