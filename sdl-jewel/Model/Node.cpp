//
//  Node.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 25/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "Node.h"

namespace jewel {
	
const Uint8 Node::END = 255;

void Node::setNeighbors(Uint8 up, Uint8 down, Uint8 left, Uint8 right)
{
	neighbors = up;
	Uint32 temp = down;
	neighbors |= (temp << 8);
	temp = left;
	neighbors |= (temp << 16);
	temp = right;
	neighbors |= (temp << 24);
}
	
}