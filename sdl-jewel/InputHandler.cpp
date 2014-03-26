//
//  InputHandler.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "InputHandler.h"
#include <cmath>

namespace jewel {
	
const int InputHandler::offsetX = 240;
const int InputHandler::offsetY = 192;
	
InputHandler::InputHandler(InputDelegate* delegate, Table* table) : delegate(delegate), table(table)
{
	//empty
}

void InputHandler::setProcessing(bool process)
{
	ignoreEvents = process;
}
	
void InputHandler::newEvent(SDL_Event* e)
{
	if (ignoreEvents) {
		return;
	}
	
	if (e->type == SDL_MOUSEBUTTONUP) {
		if (isInsideTableBounds(e)) {
			delegate->nodeTouchedAt(indexForEvent(e));
		}
	}
	
	if (e->type == SDL_MOUSEMOTION) {
		if (isInsideTableBounds(e) && ((e->motion.state) == SDL_BUTTON_LMASK)) {
			Direction direction;
			int index = 0;
			if (directionForMouseEvent(e, &direction, &index)) {
				delegate->nodeSlidTo(index, direction);
			}
		}
	}

}
	
bool InputHandler::isInsideTableBounds(SDL_Event* e)
{
	int x = e->button.x;
	int y = e->button.y;
	
	if ((x>offsetX) && (x<(offsetX+640)) && (y>offsetY) && (y<(offsetY + 640)) ){
		return true;
	}
	
	return false;
}

int InputHandler::indexForEvent(SDL_Event* e)
{
	int x = 0;
	int y = 0;
	if (e->type == SDL_MOUSEBUTTONUP) {
		x = e->button.x;
		y = e->button.y;
	} else if (e->type == SDL_MOUSEMOTION) {
		x = e->motion.x;
		y = e->motion.y;
	}

	x-=offsetX;
	y-=offsetY;
	
	x/=80;
	y/=80;
	
	return (y*8 + x);
}
	
const int InputHandler::moveTreshhold = 10;
	
bool InputHandler::directionForMouseEvent(SDL_Event* e, Direction* direction, int* index)
{
	*index = indexForEvent(e);
	
	int xrel = e->motion.xrel;
	int yrel = e->motion.yrel;
	if (std::abs(xrel) > std::abs(yrel)) {
		if (xrel > moveTreshhold) {
			*direction = Direction::Right;
			return true;
		} else if (xrel < -moveTreshhold) {
			*direction = Direction::Left;
			return true;
		} else {
			return false;
		}
	}
	
	if (yrel > moveTreshhold) {
		*direction = Direction::Down;
		return true;
	} else if (yrel < -moveTreshhold) {
		*direction = Direction::Up;
		return true;
	} else {
		return false;
	}
	
}
	
} //namespace