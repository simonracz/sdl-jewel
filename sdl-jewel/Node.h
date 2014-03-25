//
//  Node.h
//  sdl-jewel
//
//  Created by Simon Racz on 24/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__Node__
#define __sdl_jewel__Node__

#include "SDL2/SDL.h"
#include <utility>

namespace jewel {

enum class NodeType : char {
	Green = 0,
	Red,
	Yellow,
	Blue,
	Purple,
	None
};

/**
 * The current maximum table size is 15x15
 * Index 255 means there is no neighbor
 * This Node is very general. It supports complex levels, e.g. antigravity
 * A more general Node could store a state too, e.g. it could change it's neighbors based on it's actual state.
 */
struct Node{
public:
	Uint32 neighbors{0xFFFFFFFF};
	NodeType type{NodeType::None};
	Uint8 index{0};
	
	inline Node();
	inline Node(Uint8 index, NodeType type);
	inline Node(Uint8 index, NodeType type, Uint8 up, Uint8 down, Uint8 left, Uint8 right);
	
	inline void setNeighbors(Uint8 up, Uint8 down, Uint8 left, Uint8 right);
	
	inline int up();
	inline int down();
	inline int left();
	inline int right();
	
	inline int getIndex();
	
	inline bool operator==(const Node& theOther);
	inline bool operator!=(const Node& theOther);
	
	inline void swap(Node& theOther);
	
	static const int END;
};

//Node implementation
int Node::up()
{
	return (neighbors & 0xFF);
}
int Node::down()
{
	return ((neighbors>>4) & 0xFF);
}
int Node::left()
{
	return ((neighbors>>8) & 0xFF);
}
int Node::right()
{
	return ((neighbors>>12) & 0xFF);
}
int Node::getIndex()
{
	return index;
}

Node::Node()
{
	//empty
}

Node::Node(Uint8 index, NodeType type) : index(index), type(type)
{
	//empty
}

Node::Node(Uint8 index, NodeType type, Uint8 up, Uint8 down, Uint8 left, Uint8 right) : index(index), type(type)
{
	setNeighbors(up, down, left, right);
}

void Node::setNeighbors(Uint8 up, Uint8 down, Uint8 left, Uint8 right)
{
	neighbors = up;
	Uint32 temp = down;
	neighbors |= (temp << 4);
	temp = left;
	neighbors |= (temp << 8);
	temp = right;
	neighbors |= (temp << 12);
}

bool Node::operator==(const Node& theOther)
{
	return (index == theOther.index);
}
bool Node::operator!=(const Node& theOther)
{
	return (index != theOther.index);
}

void Node::swap(Node& theOther)
{
	std::swap(index, theOther.index);
	std::swap(neighbors, theOther.neighbors);
	std::swap(type, theOther.type);
}

} //namespace
	
#endif /* defined(__sdl_jewel__Node__) */
